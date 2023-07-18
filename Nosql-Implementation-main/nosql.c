//    strcat(location , " >nul 2>nul"); the > 2> are redirections to avoid unnecessary details being printed on the terminal
//

#include "nosql.h"
#include "Encryption/cipher.h"
#include <stdio.h>
#include <sys/ioctl.h> // for getting dimensions of the terminal window
#include <stdlib.h>
#include <string.h> // for strcmp
#include <ctype.h>  // for toLower
#include <unistd.h> // for getPassword command
#include "globals/globals.h"
#include "DocumentHashmap/DocumentHashMap.h"

#define SIZE 32

#define USER_ALREADY_EXISTS 0
#define PASSWORDS_MATCH 1
#define PASSWORDS_DO_NOT_MATCH 2
#define COMMAND_POSTFIX " >nul 2>nul"
#define VALID_USER_NAME 1
#define INVALID_USER_NAME 0

#define VALUE_SET 0
#define VALUE_NOT_SET 1
typedef enum Commands
{
    ls,                //
    ls_users,          //
    ls_documents,      //
    ls_collections,    //
    man,               //
    login,             //
    logout,            //
    create,            //
    create_user,       //
    create_collection, //
    create_document,   //
    delete,            //
    delete_user,       //
    delete_collection, //
    delete_document,   //
    delete_data,        // 
    export,             //
    export_user,        //
    export_collection,  //
    export_document,    //
    use_document,   //
    use_collection, //
    update_document,    // 
    clear,              //
    quit,               //
    open_document,      //
    find_field,
    show_current_user,
    NOP // Command used to indicate that the command inputted by the user is Not a Proper command
} commands;

struct winsize sz;
Globals globals; // declaring global structure for cross library fields


void println()
{
    printf("===================================================================================================================");
    return;
}

void printDashes(int length)
{
    for (int i = 0; i <= length + 1; i++)
    {
        printf("-");
    }
    printf("\n\n");
}

void printHeading(char *str)
{
    // char * str = ;
    int length = getLength(str);
    for (int i = 0; i < sz.ws_col / 2 - length / 2; i++)
        printf(" ");
    printf("%s\n", str);
    for (int i = 0; i < sz.ws_col / 2 - length / 2 - 2; i++)
        printf(" ");
    printDashes(length);
    return;
}

void logOut()
{
    if (strcmp(globals.user, "") == 0)
        printf("user has to be logged in for using `logout` command.\n");
    else
    {
        printf("user `%s` ", globals.user);
        strcpy(globals.user, "");
        strcpy(globals.collection, "");
        strcpy(globals.document, "");
        printf("has logged out successfully.\n");
    }
    return;
}

void printDeclaration(char *str)
{
    for (char *p = str; *p != '\0'; p++)
    {
        printf("   ");
        for (int j = 2; j < sz.ws_col - 3; j++)
        {
            if (*p == '\0')
                break;
            printf("%c", *p);
            p++;
        }
        if (*p == '\0')
            break;
        printf(" \n");
    }
    printf(" \n");

    // str = "Available commands are"
    // for()

    return;
}

void getchSafe()
{
    printf("Press any key to continue.\n :");
    if (getch() == '\033')
    {
        getch();
        getch();
    }
    return;
}

void clearInputBuffer()
{
    char temp = getch();
    while (temp != '\n')
    {
        if (temp == '\033')
        {
            getch();
            getch();
            break;
        }
        temp = getch();
    }
    return;
}

void printAvailableCommands()
{
    char *str = "Available commands are ls,man,login,create. Use command man for more details\n\n";
    printf("   %s", str);
    return;
}

void printWelcomeMessage()
{
    printHeading("Welcome to NoSQL implementation using C.");
    printDeclaration("This project is developed under the guidance of Prof. Ashwini Matange ma'am by the students Pratyay Dhond, Sarvesh Kulkarni and Sohel Bargir of Computer Engineering Div 2.");
    printAvailableCommands();
    return;
}

void toLower(char *input)
{
    int length = getLength(input);
    input[length - 2] = '\0';
    for (int i = 0; i < length - 1; i++)
    {
        input[i] = tolower(input[i]);
    }
    // printf("length -2 = '%d'",input[length-2]);
    for (int i = length - 1; i >= 0; i--)
        if (input[i] == (char)13)
        {
            input[i] == '\0';
            break;
        }
    return;
}

void displayMAN()
{
    system("clear");

    printHeading("Manual Page for NoSQL Implementation");

    FILE *fptr = fopen(".manual", "r");
    char *temp = calloc(200, sizeof(char));
    while (fgets(temp, 200, fptr))
    {
        printf("%s", temp);
    }
    printf("\n");
    fclose(fptr);
    free(temp);

    printDashes(getLength("Press any key to continue.\n :"));
    getchSafe();
    // This test case is explicitly for handling arrow presses, when a user presses an arrow 3 characters are put in the input stream '\033', '[' and either A,B,C,D
    system("clear");
}

char *getPassword(char *str)
{
    char *password = (char *)malloc(sizeof(char) * SIZE);
    int i = 0;
    int ch;

    // prints the do you want to enter password wala statement, do not comment
    printf("%s", str);
    while ((ch = getch()) != '\n')
    {
        if (ch == '\033')
        {
            getch(); // this case deals with the input of arrow keys in pass word
            getch();
            continue;
        }
        if (ch == 127 || ch == 8)
        { // handle backspace
            if (i != 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    return password;
}

int checkIfUserExists(char *username, char *str, char *declaration)
{
    char command[100] = "ls -d .root/";
    strcat(command, username);
    strcat(command, COMMAND_POSTFIX);
    int x = system(command);

    system("clear");
    printHeading(str);
    printDeclaration(declaration);
    printf("Enter username : %s\n", username);

    if (x == 0)
        return USER_ALREADY_EXISTS;
    return create_user;
}

void createUserDirectoryAndFiles(char *username, char *password)
{
    char command[100] = "mkdir '.root/";
    strcat(command, username);
    strcat(command, "'");
    strcat(command, COMMAND_POSTFIX);
    system(command);

    strcpy(command, "touch .root/");
    strcat(command, username);
    strcat(command, "/.pass");
    strcat(command, COMMAND_POSTFIX);
    system(command);

    char *encryptedPassword = Encrypt(password);

    // Writing Encrypted Password to file
    char passwordFile[100] = ".root/";
    strcat(passwordFile, username);
    strcat(passwordFile, "/.pass");
    FILE *fptr = fopen(passwordFile, "w+");
    fprintf(fptr, "%s", encryptedPassword);
    fclose(fptr);
    free(encryptedPassword);
    return;
    // system("clear");
}

int checkPasswords(char *password, char *confirmPassword)
{

    if (strcmp(password, confirmPassword) == 0)
    {
        free(confirmPassword);
        return PASSWORDS_MATCH;
    }
    free(password);
    free(confirmPassword);
    printf("ERROR! Both Passwords must be the same! Press any key to continue...\n");
    getchSafe();
    return PASSWORDS_DO_NOT_MATCH;
}

int checkUserName(char *username)
{
    char *p = username;
    while (*p != '\0')
    {
        if (isalnum(*p) == 0)
            if (*p != '_')
                return INVALID_USER_NAME;
        p++;
    }
    return VALID_USER_NAME;
}

void createUser()
{
    system("clear");

    printHeading("Create New User");
    char *username = calloc(100, sizeof(char));
    char input;

    printf("Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O) \n");
    printf("Enter username: ");
    scanf("%s", username);

    if (checkUserName(username) == INVALID_USER_NAME)
    {
        printf("Incorrect username! User name can only contain A-Z,a-z,0-9 and underscores.\n");
        getchSafe();
        return;
    }

    if (checkIfUserExists(username, "Create New User", "Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O)") == USER_ALREADY_EXISTS)
    {
        printf("USER ALREADY EXISTS. Try picking a new username or logging in.\n");
        getchSafe();
    }
    else
    {
        char *password;
        char *confirmPassword;

        // takes input till both passwords are the same
        do
        {
            system("clear");
            printHeading("Create New User");
            printDeclaration("Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O) ");
            printf("Enter username: %s\n", username);
            password = getPassword("Enter Password  : ");
            confirmPassword = getPassword("Confirm Password: ");
        } while (checkPasswords(password, confirmPassword) == PASSWORDS_DO_NOT_MATCH);

        printf("Creating user...\n");
        createUserDirectoryAndFiles(username, password);
        printf("User has been created successfully.\n Do you want to display your password? [Y/N]\n : ");

        input = getch();
        if (input == '\033')
        {
            getch();
            getch();
        }

        if (input == 'y' || input == 'Y')
        {
            printf("Password : %s\n", password);
            printf("Press return key to continue.\n :");
            scanf("%c", &input);
            clearInputBuffer();
        }
        free(password);
        free(username);
    }
    return;

    // printHeading()
}

int getInput()
{
    char *input = (char *)calloc(100, sizeof(char)); // calloced to get an array initialised to 0
    int command = NOP;
    fgets(input, 100, stdin);
    if (strcmp(input, "\n") == 0)
        fgets(input, 100, stdin);
    toLower(input);
    for (int i = getLength(input) - 1; i >= 0; i--)
    {
        if (isalpha(input[i]))
        {
            input[i + 1] = '\0';
            break;
        }
    }

    // printf("input -> `%s`\n",input);
    if (strcmp(input, "man") == 0)
        command = man;
    else if (strcmp(input, "clear") == 0)
        command = clear;
    else if (strcmp(input, "ls") == 0)
        command = ls;
    else if(strcmp(input,"whoami") == 0)
        command = show_current_user;
    else if (strcmp(input, "ls users") == 0 || strcmp(input, "ls user") == 0)
        command = ls_users;
    else if (strcmp(input, "ls docs") == 0 || strcmp(input, "ls documents") == 0)
        command = ls_documents;
    else if (strcmp(input, "ls collections") == 0 || strcmp(input, "ls cols") == 0)
        command = ls_collections;
    else if (strcmp(input, "show") == 0)
        command = ls;
    else if (strcmp(input, "show users") == 0 || strcmp(input, "show user") == 0)
        command = ls_users;
    else if (strcmp(input, "show docs") == 0 || strcmp(input, "show documents") == 0)
        command = ls_documents;
    else if (strcmp(input, "show collections") == 0 || strcmp(input, "show cols") == 0)
        command = ls_collections;
    else if (strcmp(input, "login") == 0)
        command = login;
    else if (strcmp(input, "logout") == 0)
        command = logout;
    else if (strcmp(input, "create") == 0)
        command = create;
    else if (strcmp(input, "create user") == 0)
        command = create_user;
    else if (strcmp(input, "create doc") == 0 || strcmp(input, "create document") == 0)
        command = create_document;
    else if (strcmp(input, "create collection") == 0 || strcmp(input, "create col") == 0)
        command = create_collection;
    else if (strcmp(input, "remove user") == 0 || strcmp(input, "rm user") == 0)
        command = delete_user;
    else if (strcmp(input, "remove col") == 0 || strcmp(input, "rm col") == 0)
        command = delete_collection;
    else if (strcmp(input, "remove collection") == 0 || strcmp(input, "rm collection") == 0)
        command = delete_collection;
    else if (strcmp(input, "remove doc") == 0 || strcmp(input, "rm document") == 0)
        command = delete_document;
    else if (strcmp(input, "remove document") == 0 || strcmp(input, "rm doc") == 0)
        command = delete_document;
    else if (strcmp(input, "use col") == 0 || strcmp(input, "use collection") == 0)
        command = use_collection;
    else if (strcmp(input, "use doc") == 0 || strcmp(input, "use document") == 0)
        command = use_document;
    else if (strcmp(input, "export") == 0)
        command = export;
    else if (strcmp(input, "export user") == 0)
        command = export_user;
    else if (strcmp(input, "export doc") == 0 || strcmp(input, "export document") == 0)
        command = export_document;
    else if (strcmp(input, "export collection") == 0 || strcmp(input, "export col") == 0)
        command = export_collection;
    else if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0)
        command = quit;
    else if (strcmp(input, "open doc") == 0 || strcmp(input, "open document") == 0)
        command = open_document;
    else if (strcmp(input, "update doc") == 0 || strcmp(input, "update document") == 0)
        command = update_document;
    else if (strcmp(input, "rm field") == 0 || strcmp(input, "remove field") == 0)
        command = delete_data;
    else if (strcmp(input, "find field") == 0 || strcmp(input, "find key") == 0)
        command = find_field;
    else
        command = NOP;
    // use document
    // use collection
    free(input);
    return command;
}

void showUsers()
{
    system(" ls .root/ >> users");
    FILE *fptr = fopen("users", "r");
    if (!fptr)
        return;
    char temp[SIZE] = "";
    printf("Users : \n");
    int j = 0;
    int code = 0;
    while (fscanf(fptr, "%s", temp))
    {
        if (feof(fptr))
            break;
        printf("  %s\n", temp);
    }
    printf("\n");
    fclose(fptr);
    system("rm users >nul 2>nul");
}

void showCollections()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login to view your collections.\n");
        return;
    }

    char command[100] = "";
    strcpy(command, "ls '.root/");
    strcat(command, globals.user);
    strcat(command, "/' >> collections");
    system(command);

    FILE *fptr = fopen("collections", "r");
    if (!fptr)
        return;
    char temp[SIZE] = "";
    printf("Collections : \n");

    while (fscanf(fptr, "%s", temp))
    {
        if (feof(fptr))
            break;
        printf("  %s\n", temp);
    }
    printf("\n");
    fclose(fptr);
    system("rm collections >nul 2>nul");
    return;
}

// Function not tested yet
void showDocuments_Frontend()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login to view your Documents.\n");
        return;
    }

    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to select a collection to view the Documents.\n");
        return;
    }

    char command[100];
    strcpy(command, "ls '.root/");
    strcat(command, globals.user);
    strcat(command, "/");
    strcat(command, globals.collection);
    strcat(command, "/");
    strcat(command, "' >> documents");
    system(command);

    FILE *fptr = fopen("documents", "r");
    if (!fptr)
        return;
    char temp[SIZE] = "";
    printf("Documents : \n");

    while (fscanf(fptr, "%s", temp))
    {
        if (feof(fptr))
            break;
        printf("  %s\n", temp);
    }
    printf("\n");
    fclose(fptr);
    system("rm documents >nul 2>nul");
    return;
}

int validateUser(char *username)
{
    int code;
    // printf("Enter password : ");
    char *password = (char *)malloc(sizeof(char) * SIZE);
    if (!password)
        return PASSWORDS_DO_NOT_MATCH;
    fgets(password, SIZE, stdin);
    password = getPassword("Enter password : ");
    if (password[0] == '\n')
        password = getPassword("Enter password : ");
    // fgets(password,SIZE,stdin);
    // password[getLength(password)-2] = '\0'; // replaces /n from the password

    strcpy(password, Encrypt(password));

    char *filename = (char *)calloc(100, sizeof(char));
    strcat(filename, ".root/");
    strcat(filename, username);
    strcat(filename, "/.pass");

    FILE *fptr = fopen(filename, "r");
    if (!fptr)
    {
        printf("password file read failed!");
        return PASSWORDS_DO_NOT_MATCH;
    }

    char *encryptedPass = (char *)malloc(sizeof(char) * SIZE);
    fgets(encryptedPass, SIZE, fptr);
    if (encryptedPass[getLength(encryptedPass) - 2] == '\n')
        encryptedPass[getLength(encryptedPass) - 2] = '\0';

    if (strcmp(password, encryptedPass) == 0)
        code = PASSWORDS_MATCH;
    else
        code = PASSWORDS_DO_NOT_MATCH;

    fclose(fptr);
    return code;
}

void removeUser()
{
    system("clear");
    printHeading("Remove User");
    printDeclaration("User removal is a dangerous process! All the collections and the documents of the user would be deleted along with the user metadata. Please make sure that you are at the right place before proceeding.");
    printf("Enter username : ");
    char *username = (char *)calloc(100, sizeof(char));
    fscanf(stdin, "%s", username);
    char command[100] = "";
    // char command[100] = "ls -d '.root/";
    // strcat(command, username);
    // strcat(command, "'");
    // int code = system(command);
    int code = checkIfUserExists(username, "Remove User", "User removal is a dangerous process! All the collections and the documents of the user would be deleted along with the user metadate. Please make sure that you are at the right place before proceeding.");
    if (code == 0)
    {
        code = validateUser(username);
        if (code == PASSWORDS_MATCH)
        {
            strcpy(command, "rm -r '.root/");
            strcat(command, username);
            strcat(command, "'");
            strcat(command, COMMAND_POSTFIX);
            system(command);
            if (strcmp(globals.user, username) == 0)
                logOut();
            printf("User `%s` deleted successfully!\n", username);
        }
        else
        {
            printf("Incorrect Password! User cannot be deleted with incorrect credentials.");
        }
        getchSafe();
    }
    else
    {
        printf("User does not exist. Check username again or try `ls users` to get list of users\n");
        getchSafe();
    }
    free(username);
    return;
}

void openDocument_FrontEnd()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to be logged in to view a document.\n");
        return;
    }

    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to select a collection to view a document.\n");
        return;
    }

    if (strcmp(globals.document, "") == 0)
    {
        printf("You need to choose the document to view. use command `use doc`\n");
        return;
    }

    showFieldsDocuments();
    destroyTreeHelper();
    return;
}

int checkUser(char *username)
{
    char command[100] = "ls -d .root/";
    strcat(command, username);
    strcat(command, COMMAND_POSTFIX);
    int x = system(command);
    if (x == 0)
        return USER_ALREADY_EXISTS;
    else
        return -1;
}
void loginUser()
{

    system("clear");
    printHeading("User Login");
    printDeclaration("Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O) ");
    printf("Enter username : ");
    char *username = (char *)malloc(sizeof(char) * SIZE);
    fscanf(stdin, "%s", username);
    int code = checkIfUserExists(username, "User Login", "Username can only consist of uppercase,lowercase character, 0-9 (and underscores if you wish :O) ");
    if (code == USER_ALREADY_EXISTS)
    {
        code = validateUser(username);
        if (code == PASSWORDS_DO_NOT_MATCH)
        {
            printf("Incorrect password! Login failed.\n");
            getchSafe();
        }
        else
        {
            printf("Welcome `%s`, you have now successfully logged in.\n", username);
            strcpy(globals.user, username);
            getchSafe();
        }
    }
    else
    {
        printf("User does not exists. Try `ls users` command to see the list of existing users.\n");
        getchSafe();
    }
    return;
}

void createCollection()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login first in order to create a collection.\n");
        return;
    }

    char *str = "Enter Collection Name : ";
    char *collectionName = (char *)malloc(sizeof(char) * 100);
    // printDashes(getLength(str));
    printf("%s", str);
    fscanf(stdin, "%s", collectionName);
    // printf("%s\n",collectionName);

    char command[100] = "ls -d ";
    char location[100] = ".root/";
    strcat(location, globals.user);
    strcat(location, "/");
    strcat(location, collectionName);
    strcat(location, COMMAND_POSTFIX);
    strcat(command, location);
    int x = system(command);
    if (x == 0)
    {
        printf("The collection `%s` already exists\n", collectionName);
    }
    else
    {
        strcpy(command, "mkdir ");
        strcat(command, location);
        system(command);
        printf("The collection `%s` has been created successfully.\n", collectionName);
    }
}

void createDocument_FrontEnd()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to be logged in to create a document.\n");
        return;
    }
    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to have selected a collection to create a document.\n");
        return;
    }

    char *str = "Enter Document Name : ";
    char *documentName = (char *)malloc(sizeof(char) * 100);
    printf("%s", str);
    fscanf(stdin, "%s", documentName);
    // printf("%s\n",documentName);

    char command[100] = "ls -d ";
    char location[100] = ".root/";

    strcat(location, globals.user);
    strcat(location, "/");
    strcat(location, globals.collection);
    strcat(location, "/");
    strcat(location, documentName);
    strcat(location, COMMAND_POSTFIX);
    strcat(command, location);

    strcpy(globals.document, documentName);

    int x = system(command);

    if (x == 0)
    {
        printf("Document Already exists. use command `#BOOKMARK` to update document");
    }
    else
    {

        printf("Document `%s` created successfully. You are into Data insertion mode now.\n Press enter twice to save your changes to the document.\n\n", documentName);
        int carriageReturnCount = 0;
        int inputFlag = 1;
        char input[100];
        char key[30] = "\0", value[100] = "\0", dataType[20] = "\0";

        fgets(input, 2, stdin);
        Pair pairs;
        initPair(&pairs);
        while (inputFlag)
        {
            fgets(input, 100, stdin);
            char *p = input;
            int keyIndex = 0;
            int valueIndex = 0;
            int keyValueBAR = 0; // if 0 key, else value
            if (strcmp(input, "\n") == 0)
            {
                carriageReturnCount++;
                // printf("carriage count ->  %d\n",carriageReturnCount);
                if (carriageReturnCount == 2)
                    break;
                continue;
            }
            else
            {
                carriageReturnCount = 0;
            }

            while (*p != '\0')
            {
                if (*p == ':')
                {
                    if (keyValueBAR == 0)
                    {
                        key[keyIndex++] = '\0';
                        // printf("*p+1 = %c\n",*(p+1));

                        if (*(p + 1) == '"')
                            strcpy(dataType, "STRING");
                        else if (*(p + 1) == '\'')
                            strcpy(dataType, "CHARACTER");
                        else if (*(p + 1) == 'T' || (*p + 1) == 'F')
                            strcpy(dataType, "BOOLEAN");
                        else
                            strcpy(dataType, "INTEGER");
                    }
                    keyValueBAR++;
                }
                else if (keyValueBAR == 0)
                    key[keyIndex++] = *p;
                else
                {
                    value[valueIndex++] = *p;
                    int isInteger = strcmp(dataType, "INTEGER");

                    if (isInteger == 0 && *p != '\n' && *p != '.' && isdigit(*p) == 0)
                    {
                        printf("Error! Incorrect Input type. Please refer to manual page for more details about syntax to follow.\n");
                        printf("ERROR CODE: failed to parse data type. Assumed INTEGER but input contains CHARACTER\n");
                        freePairs(&pairs);
                        return;
                    }
                    if (isInteger == 0 && *p == '.')
                        strcpy(dataType, "DOUBLE");
                }
                p++;
            }
            value[valueIndex - 1] = '\0';
            if (keyValueBAR == 0 && carriageReturnCount != 1)
            {
                printf("Incorrect INPUT format. refer to manual for input formats.\n");
                return;
            }

            if (strcmp(dataType, "STRING") == 0 || strcmp(dataType, "CHARACTER") == 0)
            {
                int i = 0;
                for (; i < getLength(value) - 2; i++)
                {
                    value[i] = value[i + 1];
                }
                value[i - 1] = '\0';
            }

            appendToPair(&pairs, key, value, dataType);
        }
        char command[100];
        destroyTreeHelper();
        helpInsertingIntoDocumentFile(&pairs);
        freePairs(&pairs);
    }
    strcpy(globals.document, "");
    free(documentName);
    return;
}

void useCollection()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to be logged in to use a collection.\n");
        return;
    }
    char *collectionName = (char *)malloc(sizeof(char) * 100);
    printf("Enter Collection Name : ");
    fscanf(stdin, "%s", collectionName);

    char command[100] = "ls -d ";
    char location[100] = ".root/";
    strcat(location, globals.user);
    strcat(location, "/");
    strcat(location, collectionName);
    strcat(location, COMMAND_POSTFIX);
    strcat(command, location);
    int x = system(command);

    if (x == 0)
    {
        strcpy(globals.collection, collectionName);
        strcpy(globals.document, "");
        printf("Selected Collection `%s`.\n", collectionName);
        return;
    }
    else
    {
        printf("Collection does not exist. use `ls collections` to view all your collections.\n");
        return;
    }
}

void useDocument()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to be logged in to use a collection.\n");
        return;
    }
    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to have selected a collection to use a document.\n");
        return;
    }

    char *documentName = (char *)malloc(sizeof(char) * 100);
    printf("Enter document Name : ");
    fscanf(stdin, "%s", documentName);

    char command[100] = "ls -d ";
    char location[100] = ".root/";
    strcat(location, globals.user);
    strcat(location, "/");
    strcat(location, globals.collection);
    strcat(location, "/");
    strcat(location, documentName);
    strcat(location, COMMAND_POSTFIX);
    strcat(command, location);
    int x = system(command);
    if (x == 0)
    {
        strcpy(globals.document, documentName);
        printf("Selected Document `%s`.\n", documentName);
    }
    else
    {
        printf("Document does not exist. use `ls docs` to use a document.\n");
    }
    return;
}

void removeCollection()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You must be logged in to delete a collection\n");
        return;
    }

    printf("Enter Collection Name : ");
    char *collectionName = (char *)calloc(100, sizeof(char));
    fscanf(stdin, "%s", collectionName);

    char command[100] = "ls -d ";
    char location[100] = ".root/";
    strcat(location, globals.user);
    strcat(location, "/");
    strcat(location, collectionName);
    strcat(location, COMMAND_POSTFIX);
    strcat(command, location);
    int code = system(command);
    // printf("`%s` `%s` %d\n",location,command,code);
    if (code == 0)
    {
        code = validateUser(globals.user);
        if (code == PASSWORDS_MATCH)
        {
            strcpy(command, "rm -r ");
            strcat(command, location);
            system(command);
            printf("Collection `%s` deleted successfully!\n", collectionName);
        }
        else
        {
            printf("Incorrect Password! Collection cannot be deleted with incorrect credentials.\n");
        }
    }
    else
    {
        printf("Collection does not exist. Check Collection Name again or try `ls collections` to get list of collections\n");
    }
    free(collectionName);
    return;
}

void removeDocument()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You must be logged in to delete a collection\n");
        return;
    }

    if (strcmp(globals.collection, "") == 0)
    {
        printf("You must have a collection selected to delete a document\n");
        return;
    }

    char *str = "Enter Document Name : ";
    char *documentName = (char *)malloc(sizeof(char) * 100);
    // printDashes(getLength(str));
    printf("%s", str);
    fscanf(stdin, "%s", documentName);

    char command[100] = "ls -d ";
    char location[100] = ".root/";

    strcat(location, globals.user);
    strcat(location, "/");
    strcat(location, globals.collection);
    strcat(location, "/");
    strcat(location, documentName);
    strcat(location, COMMAND_POSTFIX);
    strcat(command, location);

    int code = system(command);
    // printf("`%s` `%s` %d\n",location,command,code);
    if (code == 0)
    {
        code = validateUser(globals.user);
        if (code == PASSWORDS_MATCH)
        {
            strcpy(command, "rm -r ");
            strcat(command, location);
            system(command);
            printf("Document `%s` deleted successfully!\n", documentName);
        }
        else
        {
            printf("Incorrect Password! Document cannot be deleted with incorrect credentials.\n");
        }
    }
    else
    {
        printf("Document does not exist. Check Document Name again or try `ls docs` to get list of documents\n");
    }
    free(documentName);
    return;
}

void exportUser_FrontEnd()
{
    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login in order to export User data.\n");
        return;
    }

    char command[100] = "mkdir ";
    char location[80] = "exports_";
    strcat(location, globals.user);
    strcat(location, "");
    strcat(command, location);
    strcat(command, COMMAND_POSTFIX);
    system(command);
    int code = exportUser(globals.user);
    if(!code)
        printf("Error! Exporting Failed. Please try again, if error persists try contacting the developers.\n");

return;
}

void exportCollection_FrontEnd()
{

    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login in order to export User data.\n");
        return;
    }

    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to selecta a collection in order to export the collection.\n");
        return;
    }

    char command[100] = "mkdir ";
    char location[80] = "'exports_";
    strcat(location, globals.user);
    strcat(location, "'");
    strcat(command, location);
    strcat(command, COMMAND_POSTFIX);
    system(command);

    int code = exportCollection(globals.user,globals.collection);
    if(!code)
        printf("Error! Exporting Failed. Please try again, if error persists try contacting the developers.\n");
    return;
}

void exportDocument_FrontEnd()
{

    char command[100] = "";

    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login in order to export User data.\n");
        return;
    }

    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to select a collection in order to export the collection.\n");
        return;
    }

    if (strcmp(globals.document, "") == 0)
    {
        printf("You need to select a document in order to export the document.\n");
        return;
    }
    sprintf(command, "mkdir exports_%s", globals.user);
    system(command);
    int code = exportDocument(globals.user, globals.collection, globals.document);
    if(!code)
        printf("Error! Exporting Failed. Please try again, if error persists try contacting the developers.\n");
    // sprintf(command, "rmdir exports_%s",globals.user);
    // exportUser(globals.user);
    return;
}

void updateDocument_frontEnd()
{

    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login in order to export User data.\n");
        return;
    }

    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to select a collection in order to export the collection.\n");
        return;
    }

    if (strcmp(globals.document, "") == 0)
    {
        printf("You need to select a document in order to export the document.\n");
        return;
    }

    showFieldsDocuments();
    printf("\n");
    int carriageReturnCount = 0;
    int inputFlag = 1;
    char input[100];
    char key[30] = "\0", value[100] = "\0", dataType[20] = "\0";
    Pair pairs;
    initPair(&pairs);
    while (inputFlag)
    {
            fgets(input, 100, stdin);
            char *p = input;
            int keyIndex = 0;
            int valueIndex = 0;
            int keyValueBAR = 0; // if 0 key, else value
            if (strcmp(input, "\n") == 0)
            {
                carriageReturnCount++;
                // printf("carriage count ->  %d\n",carriageReturnCount);
                if (carriageReturnCount == 2)
                    break;
                continue;
            }
            else
            {
                carriageReturnCount = 0;
            }

            FILE *fptr = fopen("testop", "a+");
            while (*p != '\0')
            {
                if (*p == ':')
                {
                    if (keyValueBAR == 0)
                    {
                        key[keyIndex++] = '\0';
                        // printf("*p+1 = %c\n",*(p+1));

                        if (*(p + 1) == '"')
                            strcpy(dataType, "STRING");
                        else if (*(p + 1) == '\'')
                            strcpy(dataType, "CHARACTER");
                        else if (*(p + 1) == 'T' || (*p + 1) == 'F')
                            strcpy(dataType, "BOOLEAN");
                        else
                            strcpy(dataType, "INTEGER");
                    }
                    keyValueBAR++;
                }
                else if (keyValueBAR == 0)
                    key[keyIndex++] = *p;
                else
                {
                    value[valueIndex++] = *p;
                    int isInteger = strcmp(dataType, "INTEGER");

                    if (isInteger == 0 && *p != '\n' && *p != '.' && isdigit(*p) == 0)
                    {
                        printf("Error! Incorrect Input type. Please refer to manual page for more details about syntax to follow.\n");
                        printf("ERROR CODE: failed to parse data type. Assumed INTEGER but input contains CHARACTER\n");
                        // #BOOKMARK -> FREE PAIR HERE
                        return;
                    }
                    if (isInteger == 0 && *p == '.')
                        strcpy(dataType, "DOUBLE");
                }
                p++;
            }
            value[valueIndex - 1] = '\0';
            if (keyValueBAR == 0 && carriageReturnCount != 1)
            {
                printf("Incorrect INPUT format. refer to manual for input formats.\n");
                return;
            }

            if (strcmp(dataType, "STRING") == 0 || strcmp(dataType, "CHARACTER") == 0)
            {
                int i = 0;
                for (; i < getLength(value) - 2; i++)
                {
                    value[i] = value[i + 1];
                }
                value[i - 1] = '\0';
            }

            appendToPair(&pairs, key, value, dataType);
        }
    helpUpdatingTheDocument(pairs);
}

void deleteData_frontEnd(){

    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login in order to export User data.\n");
        return;
    }

    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to select a collection in order to export the collection.\n");
        return;
    }

    if (strcmp(globals.document, "") == 0)
    {
        printf("You need to select a document in order to export the document.\n");
        return;
    }

    showFieldsDocuments();
    printf("\nEnter `key` of the data to be deleted.\n >> ");
    char key[100];
    fscanf(stdin,"%s",key);
    int status = helpRemoveFieldFromDocument(globals.collection,globals.document,key);
return;
}

void findField_FrontEnd(){

    if (strcmp(globals.user, "") == 0)
    {
        printf("You need to login in order to export User data.\n");
        return;
    }

    if (strcmp(globals.collection, "") == 0)
    {
        printf("You need to select a collection in order to export the collection.\n");
        return;
    }

    if (strcmp(globals.document, "") == 0)
    {
        printf("You need to select a document in order to export the document.\n");
        return;
    }

    showFieldsDocuments();
    printf("\nEnter `key` of the data to be searched.\n >> ");
    char key[100];
    fscanf(stdin,"%s",key);
    int status = searchTheDocumentInFile(key);

return;
}

void test1(){
    // insertIntoDocumentHashMap("sarvesh","aserv","datra");
    // preOrder(tnode);
    // exit(0);
    // globals.collection = "a";
    // globals.user = "a";
    // globals.document = "a";

    // Pair new;
    // initPair(&new);
    // appendToPair(&new,"name","COEP","STRING");
    // appendToPair(&new,"yesorno","T","BOOLEAN");
    // appendToPair(&new,"yeda","1","INTEGER");


    //  Pair upadtePair;
    // initPair(&upadtePair);
    // appendToPair(&upadtePair,"name","YES","STRING");
    // appendToPair(&upadtePair,"yesorno","Y","BOOLEAN");
    // appendToPair(&upadtePair,"yeda","YES","STRING");

    // helpInsertingIntoDocumentFile(&new);
    // showFieldsDocuments();   
    // exit(0);
    // helpUpdatingTheDocument(upadtePair);
    
    // helpUpdatingField("name","Sarvesh", "STRING");
    // // helpRemoveFieldFromDocument(globals.collection,globals.document,"yeda");     
    // showFieldsDocuments();
    // exit(0);
    strcpy(globals.user,"test");
    // strcpy(globals.collection,"1");
    // strcpy(globals.document,"");
    // strcpy(globals.user,"sohel");
    // strcpy(globals.collection,"col1");
    // strcpy(globals.document,"doc1");

    // exportDocument_FrontEnd();
    // exportUser_FrontEnd();
    // updateDocument_frontEnd();
    // test1();
}

void displayCurrentUser(){
    if(strcmp(globals.user,"") == 0){
        printf("You need to be logged in to view current user.\n");
    }
    printf("%s\n",globals.user);
return;
}


void noSQLMenu()
{
    initGlobals();
    // test1();
    ioctl(0, TIOCGWINSZ, &sz);
    printWelcomeMessage();
    int command;
    int programRunning = 1;
    while (programRunning)
    {
        printf(">> ");
        command = getInput();
        switch (command)
        {
        case man:
            displayMAN();
            system("clear");
            printWelcomeMessage();
            break;
        case ls:
            printf("use `show` with one of the following parameters:\n");
            printf("   1. <SYNTAX> => `show users`\n");
            printf("   2. <SYNTAX> => `show docs`\n");
            printf("   3. <SYNTAX> => `show cols`\n");
            printf("use command `man` for more details\n");
            break;
        case ls_users:
            showUsers();
            break;
        case ls_collections:
            showCollections();
            break;
        case ls_documents:
            showDocuments_Frontend();
            break;
        case create:
            printf("use `create` with one of the following parameters:\n");
            printf("   1. <SYNTAX> => `create user`\n");
            printf("   2. <SYNTAX> => `create document`\n");
            printf("   3. <SYNTAX> => `create collection`\n");
            printf("use command `man` for more details\n");
            break;
        case create_user:
            createUser();
            system("clear");
            printWelcomeMessage();
            break;
        case create_collection:
            createCollection();
            break;
        case create_document:
            createDocument_FrontEnd();
            break;
        case delete:
            printf("use `remove` with one of the following parameters:\n");
            printf("   1. <SYNTAX> => `rm user`\n");
            printf("   2. <SYNTAX> => `rm doc`\n");
            printf("   3. <SYNTAX> => `rm col`\n");
            break;
        case delete_user:
            removeUser();
            system("clear");
            printWelcomeMessage();
            break;
        case delete_collection:
            removeCollection();
            break;
        case delete_document:
            removeDocument();
            break;
        case use_collection:
            useCollection();
            break;
        case use_document:
            useDocument();
            break;
        case export:
            printf("use `export` with one of the following parameters:\n");
            printf("   1. <SYNTAX> => `export user`\n");
            printf("   2. <SYNTAX> => `export doc`\n");
            printf("   3. <SYNTAX> => `export col`\n");
            printf("use command `man` for more details\n");
            break;
        case export_document:
            exportDocument_FrontEnd(); // not complete
            break;
        case export_collection:
            exportCollection_FrontEnd(); // not complete
            break;
        case export_user:
            exportUser_FrontEnd(); // not complete
            break;
        case open_document:
            openDocument_FrontEnd(); // not complete
            break;
        case show_current_user:
            displayCurrentUser();
            break;
        case login:
            if (strcmp(globals.user, "") != 0)
            {
                printf("You are already Logged in. use the command `logout` before logging in with another user\n");
                break;
            }
            loginUser();
            system("clear");
            printWelcomeMessage();
            break;
        case logout:
            logOut();
            break;
        case clear:
            ioctl(0, TIOCGWINSZ, &sz);
            system("clear");
            printWelcomeMessage();
            break;
        case quit:
            programRunning = 0;
            destroyGlobals();
            break;
        case update_document:
            updateDocument_frontEnd();
            break;
        case NOP:
            printf("Incorrect Command Syntax. Check your inputted command for typos or refer to `man`.\n");
            break;
        case delete_data:
            deleteData_frontEnd();
            break;
        case find_field:
            findField_FrontEnd();
        default:
            break;
        }
    }

    int x = system("ls -d nul >nul 2>nul");
    if(x == 0){
        system("rm nul  ");
    }
}

// refs -> https://stackoverflow.com/questions/26606003/disable-console-output-from-external-program-c