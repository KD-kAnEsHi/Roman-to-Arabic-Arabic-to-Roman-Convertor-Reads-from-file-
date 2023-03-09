            // NetID: kka210001                                                                  Name: Karl Azangue

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string database = "numbers.txt";

int arabics(string roman);
string romans(string nums);

bool arabicValidTest(string wholeLineTest);
bool romanValidTest(string wholeLineTest);

/* SUMMARY: In the main function, the program is going to prompt the user to enter the file containing the input. Once that is given the program will then open the file and read the file character by character. The first 17 character in the line are going to be stored in the variable "romanLine" and the last 4 characters are going to be stored in the variable "arabicLine". Once the program reaches the newline 22nd character in the each line ('ln' or end-of-file <EOF>). It is going to send the arabline and romanline to the boolean function "romanValidTest" and "arabicValidTest" where each individual character will be checked to see if it fits the requirment. If either function where to return false the program will replace the entire line with space and reset the varaible "arabicLine" and "romanLine" to 0 before going to the next line using seek and tell. Else if both function where to return false, the program will then check whether the first character in the file is a space (If the first character is a space, that means the line does not contains roman, but if the first character is not space that mean the line does not contain romans numeral) If the first character is a space, the program will call the "romans" function where the program will convert the arabic to numerals to roman numerals and once returned, it will then output the roman numeral inbetween the first 17 characters in the line. Else if the first character is not a space, the program will call the "arabics" function where the program will convert the roman numerals to arabic numerals and once returned, it will then output the arabic numeral inbetween the first 4 characters of the line. Once done the program will clear the "arabicLine" and "romanLine" and move on to next line, this process will go on until the program stops reading the file.*/
int main()
{
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
       string temp;  //variable for database filename
       string batch; //variable for batch filename

       cout<<"Enter File Name: ";
       cin>>temp;

       ifstream infile(temp, ios::binary);
       ofstream outfile(database, ios::binary);
       string line;
       if (infile)
            while (infile.good())
            {
                getline(infile, line);
                if (line != "")
                    outfile << line << "\n";
            }

       infile.close();
       outfile.close();
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    
    fstream file;
    string romanLine, arabicLine, roman;
    char wholeLine;
    
    int dividor = 0, arabic;
    long long int position = 0;
    
    file.open(database, ios::in | ios::out | ios::binary);  //The program opens the file in input, output and binary file, thus enebling us to not only open the file for input and output, but also enables us to use seek and tell.
    {
        if(!file.good())  //This test whether there was any error when opening the file.
        {
            cout << "file, could not be open" <<endl;
        }
        
        while(file.get(wholeLine))  //This is going to run the code character by character and store the first 17 characters in each line in the variable "romanLine" and the last 4 characters in the variable "arabicLine"
        {
            dividor++;
            
            if(dividor <= 17) //store first 17 character in each line
            {
                romanLine += wholeLine;
            }
            else if(dividor > 17 && dividor <= 21)   //store last 4 characters in each line
            {
                arabicLine += wholeLine;
            }

            if(wholeLine == '\n' || file.eof())  //After the program is done storing the 21 characters in thier indiviual string, it is going to hit the newline 'ln' or end of file <EOF>. Once that happend the program will then procce to check wether the strings "romanLine" and "arabicLine" contains the appropriate characters. If false, the program will replace the entrie line with spaces else it will procceed to covert and display the missing numeral before moving to next line.(if there is one.)
            {
                if( romanValidTest(romanLine) == false || arabicValidTest(arabicLine) ==  false) //Program calls the boolean function "romanValidTest" and "arabicValidTest" where the string "romanLine" and "arabicLine" will be checked for any invalid characters. If either function where to return false the following program will run.
                {
                    romanLine = "";  //The program sets the "romanLine" and "arabicLine" to empty so the can store the information from next line.
                    arabicLine = "";
                    dividor = 0;
                    
                    position = file.tellg(); //The program stores the current location of the cursor in file in the variable "position", before it is changed in order to output the newlines. This enables the program to get back to the appropriate location once it is done outputing the spaces.
                    file.seekp(position-22); //Set the cursor at the begining of the line the program is currently at.
                    
                    for(int count = 0; count < 21; count++)  //This will go through the line and replace each character with spaces, before moving to next line.
                    {
                            file << " ";
                    }
                }
                else if(romanLine[0] == ' ')  //This checks whether the first character in the line is empty or not. This enables the program to identify whether the missing portion is the arabic or roman numeral. If the first character is missing then we are converting from arabic to roman numerals else we are converting from roman to arabic numerals.
                {
                    roman = romans(arabicLine);  //This passes the string in the string variable "arabicLine" into the function string "romans" where the arabicLine will be converted to romans numerals and returned to the main function as a string.
                    
                    romanLine = ""; //The program sets the "romanLine" and "arabicLine" to empty so the can store the information from next line.
                    arabicLine = "";
                    dividor = 0; //Reset the counter to 0 for next line.
                    
                    position = file.tellg();  //The program stores the current location of the cursor in file in the variable "position", before it is changed in order to output the newlines. This enables the program to get back to the appropriate location once it is done outputing the spaces.
                    file.seekp(position-22); //Sets the postion of the cursor at the begining of the line the program is currently at.
                    
                    file << roman;  //The program will then input the missing portion of the line (roman numerals) in the file.
                }
                else
                {
                    arabic = arabics(romanLine); //This passes the string in the string variable "romanLine" into the function string "arabics" where the roamnLine will be converted to arabics numerals and returned to the main functionas as an integer.

                    romanLine = "";
                    arabicLine = "";
                    dividor = 0;
                    
                    position = file.tellg();//The program stores the current location of the cursor in file in the variable "position", before it is changed in order to output the newlines. This enables the program to get back to the appropriate location once it is done outputing the spaces.
                    
                    file.seekp(position-5); //Sets the postion of the cursor at the 18 characters of the line the program is currently at.
                    file << arabic;  //The program will then input the missing portion of the line (arabic numerals) in the file
                }
                file.seekg(position, ios::beg); //This puts the cursor back the where it was before being change when inputting informaiton into the file.
            }
        }
        file.close();  //closes the file once the program is done executing
        
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------

bool romanValidTest(string wholeLineTest)    //In this function, the program will check whether the last 4 characters in the array (arabic values) contain any invalid characters. (letters, punctuation, or anything that is not a number.) If it contains an invalid character, the program will return false, otherwise the program will return true.
{
    
    for(unsigned long i = 0; i < wholeLineTest.length(); i++) //This for loop is used to go through each character and if any of these character where not to be I, V, X, L, C, D, M, or a space the function will return false else the function will return true.
    {
        if(wholeLineTest[i] != 'I' && wholeLineTest[i] != 'V' && wholeLineTest[i] != 'X'
        && wholeLineTest[i] != 'L' && wholeLineTest[i] != 'C' && wholeLineTest[i] != 'D'
        && wholeLineTest[i] != 'M' && wholeLineTest[i] != ' ') //I V X L C D M
        {
            return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
bool arabicValidTest(string wholeLineTest) //In this function, the program will check whether the first 17 characters in the array (roman values) contain any invalid character.(digits, punctuation, lowercase letters, uppercase letters not listed as valid, or anything that is not: I, V, X, L, C, D, M.) If it contains an invalid character, the program will return false, otherwise the program will return true.
{

    if(wholeLineTest.compare("0   ") == 0)   //This if statement is used to test whether the arabic value is 0. If that where to be the case, the function will return false.
    {
        return false;
    }
        
    for(unsigned long i = 0; i < wholeLineTest.length(); i++ )   //This for loop is used to go through each character and if any of these character where not to be a number or a space the function will return false else the function will return true.
    {
    
        if(!(isdigit(wholeLineTest[i]) || isspace(wholeLineTest[i])))
        {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------ROMAN TO ARABIC------------------------------------------------------------------
int arabics(string roman) //-In this function, the program will make use of the array of characters to convert to (arabic numerals) by associating the corresponding characters (I, V, X, L, C, D, M) with a specific number. (I=1, V=5, X=10, L=50, C=100, D=500, M=1000.) The program will check the characters from the array in set of 2’s. If the first character is greater than the second, the number of the first character gets stored in an integer variable named “total” and the program moves on to the next two characters with the second character now being the first. Else if the second character is less than the second character, the number of the first character is subtracted from the number of the second character and the answer is incremented in the values in the variable “ARABIC”. Then both characters are skipped. This will go on until the program reaches the 17th character in the array. Once this is done, the program will return the integer to main
{
    //unsigned long int stringLength = roman.length();
    int num1=0, num2=0, ARABIC = 0;
    
    /* The followig code converts a Roman numeral represented as a string roman into its corresponding integer value ARABIC. The length of the string is first computed and stored in stringLength. Then, for each pair of adjacent characters in the string, the corresponding integer values num1 and num2 are determined using a switch statement. If num1 is less than num2, it means that a subtraction is needed, so num2 - num1 is added to the ARABIC variable and the index variables i and k are incremented by 1 to skip the next character. Otherwise, num1 is simply added to ARABIC. The resulting integer ARABIC is returned as the corresponding Arabic numeral value of the input Roman numeral string.*/
    unsigned long int i, k;
    for(i = 0, k = 1; k <= roman.length(); i++, k++)
    {
        switch (roman[i])
        {
            case 'I':
            case 'i':
                num1 = 1;
                break;
            case 'V':
            case 'v':
                num1 = 5;
                break;
            case 'X':
            case 'x':
                num1 = 10;
                break;
            case 'L':
            case 'l':
                num1 = 50;
                break;
            case 'C':
            case 'c':
                num1 = 100;
                break;
            case 'D':
            case 'd':
                num1 = 500;
                break;
            case 'M':
            case 'm':
                num1 = 1000;
                break;
             default:
                num1 = 0;
                break;
        }
        
        switch (roman[k])
        {
            case 'I':
            case 'i':
                num2 = 1;
                break;
            case 'V':
            case 'v':
                num2 = 5;
                break;
            case 'X':
            case 'x':
                num2 = 10;
                break;
            case 'L':
            case 'l':
                num2 = 50;
                break;
            case 'C':
            case 'c':
                num2 = 100;
                break;

            case 'D':
            case 'd':
                num2 = 500;
                break;
            case 'M':
            case 'm':
                num2 = 1000;
                break;
            default:
                num2 = 0;
                break;
        }

        if(num1 < num2)
        {
            int num3 = num2 - num1;
            ARABIC += num3;
            i+=1;
            k+=1;
        }
        
        if(num1 >= num2)
        {
            ARABIC += num1;
        }
    }
    return ARABIC;
}

//-------------------------------------------------------------ARABIC TO ROMAN-----------------------------------------------------------------

string romans(string nums) //In this function, the program will convert the integers (arabic values) into roman values by dividing the integers by 1,000, 100, and 10. Then associating the value from each division with their corresponding “Roman numeral” (string) and appending them together in a string variable. After this is done, the program will then return the string variable to the main function.

{
    string ROMAN;
    int num = stoi(nums);  //This converts the string passed to the function as an integer thus enabling the program to manipulate it as such

    /*The following code first checks if the number is greater than or equal to 1000 and appends "M" to the result string ROMAN for every thousand. It then checks if the remaining number is greater than or equal to 100, and adds the corresponding Roman numeral using a switch statement. The same process is repeated for the tens and ones digits. The resulting string ROMAN is returned as the Roman numeral representation of the input number.*/
    if(num >= 1000)
    {
        for(int i = 0; i < num/1000; i++)
        {
            ROMAN += "M";
        }
        num %= 1000;
    }
    if(num >= 100)
    {
        switch (num/100)
        {
            case 1:
                ROMAN += "C";
                break;
            case 2:
                ROMAN += "CC";
                break;
            case 3:
                ROMAN += "CCC";
                break;
            case 4:
                ROMAN += "CD";
                break;
            case 5:
                ROMAN += "D";
                break;
            case 6:
                ROMAN += "DC";
                break;
            case 7:
                ROMAN += "DCC";
                break;
            case 8:
                ROMAN += "DCCC";
                break;
            case 9:
                ROMAN += "CM";
                break;
        }
        num %= 100;
    }
    if(num >= 10)
    {
        switch (num / 10)
        {
            case 1:
                ROMAN += "X";
                break;
            case 2:
                ROMAN += "XX";
                break;
            case 3:
                ROMAN += "XXX";
                break;
            case 4:
                ROMAN += "XL";
                break;
            case 5:
                ROMAN += "L";
                break;
            case 6:
                ROMAN += "LX";
                break;
            case 7:
                ROMAN += "LXX";
                break;
            case 8:
                ROMAN += "LXXX";
                break;
            case 9:
                ROMAN += "XC";
                break;
        }
        num %= 10;
    }
    if(num < 10)
    {
        switch (num)
        {
            case 1:
                ROMAN += "I";
                break;
            case 2:
                ROMAN += "II";
                break;
            case 3:
                ROMAN += "III";
                break;
            case 4:
                ROMAN += "IV";
                break;
            case 5:
                ROMAN += "V";
                break;
            case 6:
                ROMAN += "VI";
                break;
            case 7:
                ROMAN += "VII";
                break;
            case 8:
                ROMAN += "VIII";
                break;
            case 9:
                ROMAN += "IX";
                break;
        }
    }
    return ROMAN;
}
 
