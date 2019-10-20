struct dict_element
{
    //Each element of dictionary has a name (= word itself) and a definition.
    char word[100];
    char definition[500];

    struct dict_element *next ;

};
