/* CS261- Assignment 1 - Q.3*/
/* Name: Wei-Chien Hsu
 * Date: 07/01/2018
 * Solution description: 
 * Write a function void camelCase(char* word) where the argument of the function is a string that 
 * must consist of two or more words separated by one or more underscores such as “random_word” or 
 * "this_is_my_first_programming_assignment". 
 * 
 * camelCase(..) should remove underscores from the sentence and rewrite it in "lower camel case. 
 * Watch out for the end of the string, which is denoted by ‘\0’. You also have to make sure that 
 * an user provided input string is in valid form first before you use it for the function 
 * camelCase(..). Below are some examples of the conversions that are expected - 
 * 
 * a) "_random_ _word" should be changed to "random_word" first.
 * b) "@$random4word" should be changed to "random_word" first.
 * c) " random word " should be changed to "random_word" first.
 * d) "random word" should be changed to "random_word" first.
 * e) "RANDOM_Word" should be changed to "random_word" first.
 * f) One or more combinations from options a, b, c, d and e.
 * 
 * The strings that you must not allow as arguments are: 
 * "_", "__ _", " ", "435_%7_$$", "random", "_random_". 
 * Print “invalid input string” for such cases.
 */

#include <stdio.h>
#include <stdlib.h>

char toUpperCase(char ch){
  /* Convert ch to upper case, assuming it is in lower case currently*/
	/* If ch is in lowercase, we convert that character or return the original value */
	if(ch >= 'a' && ch <= 'z') {
		return ch-'a'+'A';
	} else {
		return ch;
	}           
}

char toLowerCase(char ch){
  /* Convert ch to lower case, assuming it is in upper case currently*/
	/* If ch is in uppercase, we convert that character or return the original value */
	if(ch >= 'A' && ch <= 'Z') {
		return ch-'A'+'a';
	} else {
		return ch;
	}             
}

int stringLength(char s[]) {
   /*Return the length of the string*/
	 int count = 0;
	 while(s[count] != '\0') {
		 count ++;
	 }
	 return count;
}

void transferToLowerCase(char s[]) {
	for(int i = 0; i < stringLength(s); i++) {
		s[i] = toLowerCase(s[i]);
	}
}

int isValidInput(char* word) {
	/* Return value : 1 mean true, 0 mean false*/
	int numberOfAlph = 0;
	int numberOfWords = 0;

	/* Empty input should return false */
	if(word[0] == '\0') {
		return 0;
	}

	/* Start from Number should return false */
	if(word[0] >= '0' && word[0] <= '9' ) {
		return 0;
	}

	/* Check if there is no character in the string */
	for(int i = 0; i < stringLength(word); i++) {
		if(word[i] >= 'a' && word[i] <= 'z') {
			numberOfAlph++;
		}
	}
	/* If there are only underscores in the string return false */
	if(numberOfAlph == 0) {
		return 0;
	}

	/* Check the number of words in the string */
	/* Check the first character and mark the number of Word */
	if(word[0] >= 'a' && word[0] <= 'z') {
		numberOfWords++;
	}

	/* Check the combination of not Character (will be changed to '_' later) with Character */
	/* Example: _abc_ddd -> 2, abcabc_ -> 1, _abcabc_abc -> 2 */
	for(int i = 0; i < stringLength(word) - 1; i++) {
		if(!(word[i] >= 'a' && word[i] <= 'z') && word[i + 1] >= 'a' && word[i + 1] <= 'z') {
			numberOfWords++;
		}
	}
	/* If there are only one word in the string return false */
	if(numberOfWords > 1) {
		return 1;
	} else {
		return 0;
	}
}

void camelCase(char* word){
	char* temp = word;
	int needAnUnderscore = 0;
	int metFirstLetter = 0;
	int count = 0;
	int tempCount = 0;

	/* Convert to conversional case*/
	/* Example: _random__word -> random_word, RANDOM_Word -> random_word, @$random4word -> random_word */
	
	while(word[count] != '\0') {
		/* If we met the not letter character dismiss the original string  */
		if(!(word[count] >= 'a' && word[count] <= 'z')) {
			count++;
			/* If we has already met first letter, need to marked needAnUnderscore as true */
			if(metFirstLetter == 1) {
				needAnUnderscore = 1;
			}
		}

		/* If we met letter character  */
		if(word[count] >= 'a' && word[count] <= 'z') {
			/* When the character we met is in the second word */
			if(needAnUnderscore == 1 && metFirstLetter == 1) {
				/* Add an underscore before the second word */
				temp[tempCount++] = '_';
				needAnUnderscore = 0;
			}
			temp[tempCount++] = word[count++];
			metFirstLetter = 1;
		}
	}
	/* Give a terminal point into the temp string array */
	temp[tempCount] = '\0';
	/* Copy to the original array with new conversional case */
	for(int i = 0; i < stringLength(temp); i++) {
		word[i] = temp[i];
	}


	/* Convert to Camel case*/
	/* Example: random_word -> randomWord */

	int len = stringLength(word);
	int newStringCount = 0;
	int oldStringCount = 0;

	for(int i = 0; i < len; i++) {
		if(word[oldStringCount] == '_') {
			/* Convert the next character as Uppercase */
			word[oldStringCount + 1] = toUpperCase(word[oldStringCount + 1]);
			oldStringCount++;
		}
		// Copy the character
		word[newStringCount++] = word[oldStringCount++];
	}
	// Add a terminal point
	word[newStringCount] = '\0';
}

int main(){

	/*Read the string from the keyboard*/
	char mystring[40];
	scanf("%[^\n]%*c",mystring);

	/* Transfer the string to a lowerCase */
	/* In order to check validation and convert to conversional case */
	transferToLowerCase(mystring);
	
	/*Call camelCase*/
	if(isValidInput(mystring) == 1) {
		camelCase(mystring);
		/*Print the new string*/
		printf("New String in Camel Case : %s \n", mystring);
	} else {
		printf("Invalid input string: %s. \n", mystring);
	}
	
	return 0;
}

