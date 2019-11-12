#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include <fcntl.h> 
#include <errno.h>
#include <dirent.h>


//pstree is what we have to reproduce

struct pstree_node {
	char name[128];
	pid_t pid;
	pid_t ppid;
	struct pstree_node * parent;
	struct pstree_node * children[128];
	struct pstree_node * next;
};

static struct pstree_node * head;

int NewNode(char *procname, pid_t pid, pid_t ppid)
{
	struct pstree_node *node;
	node = (struct pstree_node*)malloc(sizeof(struct pstree_node));
	if (node == NULL) {
		printf("Unable to allocate memory for node\n");
		return 1;
	}
	strcpy(node->name, procname);
	node->pid = pid;
	node->ppid = ppid;
	node->children[0] = NULL;
	node->parent = NULL;
	node->next = head; /* could be null, that is fine */
	head = node;
	return 0;
}

int catalog_process(char *dirname)
{
	char filename[256];
	char linebuf[256];
	char procname[256];
	char pid[32];
	char ppid[32];
	char *key;
	char *value;
	FILE *p_file;
	strcpy(filename, dirname);
	strcat(filename, "/status");
	p_file = fopen(filename, "r");
	if (p_file == NULL) {
		return 1;
	}
	while (fgets(linebuf, sizeof(linebuf), p_file) != NULL) {
		key = strtok(linebuf, ":");
		value = strtok(NULL, ":");
		if (key != NULL && value != NULL) {
			trim(key); trim(value);
			if (strcmp(key, "Pid") == 0) {
				strcpy(pid, value);
			} else if (strcmp(key, "PPid") == 0) {
				strcpy(ppid, value);
			} else if (strcmp(key, "Name") == 0) {
				strcpy(procname, value);
			}
		}
	}

	return NewNode(&procname[0], atoi(pid), atoi(ppid));
}

struct pstree_node * find_node_with_pid(pid_t pid)
{
	struct pstree_node *node;
	for (node = head; node != NULL; node = node->next) {
		if (node->pid == pid) {
			return node;
		}
	}
	return NULL;
}

int make_tree(void)
{
	int i;
	struct pstree_node *node, *pnode;

	/* now we have a valid linked list, make a tree */
	for (node = head; node != NULL; node = node->next) {
		i = 0;
		pnode = find_node_with_pid(node->ppid);
		if (pnode != NULL)
        {
			node->parent = pnode;
			while (pnode->children[i++] != NULL);
			pnode->children[i - 1] = node;
			pnode->children[i] = NULL;
		}
	}
	return 0;
}

int print_tree(struct pstree_node * root, int level)
{
	int i;
	struct pstree_node *node;
	for (i = 0; i < level; i++)
    {
		printf("  ");
	}
	printf("%s (pid: %d, ppid: %d)\n", root->name, root->pid, root->ppid);
	/* recurse on children */
	while ((node = root->children[i++]) != NULL)
    {
		print_tree(node, level + 1);
	}
	return 0;
}

int main(int argc, char *argv[])
{

	DIR *directory;
	struct dirent *directory_entry;
	char dirname[256];

    // Open directory
    directory = opendir("/proc");

    // Make sure directory opened correctly
	if (directory == NULL)
    {
		perror("Unabled to open directory");
        // Error
		return 1;
	}
	do {
		if ((directory_entry = readdir(directory)) != NULL)
        {
			if (directory_entry->d_type == DT_DIR)
            {
				strcpy(&dirname[0], "/proc");
				strcat(&dirname[0], "/");
				strcat(&dirname[0], directory_entry->d_name);
				catalog_process(dirname);
			}
		}
	} while (directory_entry != NULL);

	/* turn the list into a tree */
	make_tree();

	/* print the tree */
	struct pstree_node *node;
	for (node = head; node != NULL; node = node->next) {
		// printf("node: %s, pid: %d, ppid: %d\n", node->name, node->pid, node->ppid);
		if (node->parent == NULL) {
			print_tree(node, 0);
		}
	}

	return 0;
}