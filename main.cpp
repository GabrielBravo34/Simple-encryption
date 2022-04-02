/*
this is a small and simple program to encrypt and decrypt strings.
Developed by Gabriel Bravo Eguren.
*/

#include <iostream>
#include <vector>
#include <ctime>

//number of characters with which the program will work
const unsigned int CHARS_LENGTH = 87;

//array of characters
const char chars[CHARS_LENGTH]
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u',
    'v', 'w', 'x', 'y', 'z', '{', '}',
    '<', '>', '"', '=', '[', ']', ';',
    '1', '2', '3', '4', '5', '6', '7', 
    '8', '9', '0', 'A', 'B', 'C', 'D',
    'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y',
    'Z', '.', ',', '(', ')', '$', '%',
    '@', '#', '?', '/', '&', '!', '|',
    ':', '-', '_'
};

//generates a list (std::vector) of random positions for the char array
//example: {12, 3, 5, 67, ...}
//none of the elements of the list will be repeated
std::vector<int> getIndexList(std::string key)
{
    std::vector<int> indexList;
    bool indexationComplete = false; //when all possible positions are assigned, exit
    int index, cont = 0;
    bool repeated;
    unsigned int seed = std::hash<std::string>{}(key);

    srand(seed); //the key is the seed by which the random numbers will be created

    while(!indexationComplete)
    {
        repeated = false;

        index = rand() % CHARS_LENGTH;

        //checks if index is repeated in indexList
        for(auto i : indexList)
        {
            if(i == index) 
            {
                repeated = true;
                break;
            }
        }

        if(!repeated) 
        {
            indexList.push_back(index);
            cont++;
        }

        if(cont == CHARS_LENGTH) indexationComplete = true;
    }
    
    srand(time(NULL));

    return indexList;
}

//encrypts a message
void encrypt(std::string& message, std::string key)
{
    std::vector<int> indexList = getIndexList(key);
    int j;
    bool exit;

    for(int i = 0; i < message.length(); i++)
    {
        j = 0;
        exit = false;

        while(j < CHARS_LENGTH && !exit)
        {
            //if the current character of the message equals to its correspondent in the char array
            //replace it with its parallel random generated char
            if(message[i] == chars[j])
            {
                message[i] = chars[indexList[j]];
                exit = true;
            }

            j++;
        }
    }
}

//returns the decrypted result of the encrypted message
std::string decrypt(std::string message, std::string key)
{
    std::vector<int> indexList = getIndexList(key);
    int j;
    bool exit;

    for(int i = 0; i < message.length(); i++)
    {
        j = 0;
        exit = false;

        while(j < CHARS_LENGTH && !exit)
        {
            //if the current character of the encrypted message equals to its correspondent
            //in the random generated char list, replace it with the original char
            if(message[i] == chars[indexList[j]])
            {
                message[i] = chars[j];
                exit = true;
            }

            j++;
        }
    }

    return message;
}

int main()
{
    //Message to encrypt
    std::string myMessage = "hello, i am Gabriel Bravo and i am studying web development!";

    //Encryption and decryption password (random numbers seed)
    std::string password = "passw12";

    //Password that user will enter
    std::string password_input;

    //Ecrypt message
    encrypt(myMessage, password);

    std::cout << "Encrypted message: " << myMessage << std::endl;

    std::cout << "Enter password to see decrypted message -> ";
    std::cin >> password_input;

    //Decrypt message, if password doesnt equals 'passw12', the result will not be original message.
    std::string result = decrypt(myMessage, password_input);

    std::cout << "Decrypted message: " << result << std::endl;

    return 0;
}
