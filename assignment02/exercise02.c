#include <stdio.h>
#include <string.h>


int isPalindrome(char* word){
  int isPalindrome = 1;

  for(int i = 0; i < strlen(word) / 2; i++)
    if(word[i] != word[strlen(word) - 1 - i]){
      isPalindrome = 0;
  }

  return isPalindrome;
}

int main(void){
  char *words[] = {"level", "hello"};
  int result[2];

  for(int i = 0; i < 2; i++){
    if(isPalindrome(words[i]))
      printf("%s is palindrome.\n", words[i]);
    else
      printf("%s is not palindrome.\n", words[i]);
}

  return 0;
}
