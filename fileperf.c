// 這個程式是一個文本處理程式，用於將輸入文件中的單詞以指定的方式格式化輸出到輸出文件中
// 可以使用命令行參數指定輸入文件名、輸出文件名以及緩衝模式
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    FILE *input;
    FILE *output;
    size_t num = 0;
    char word_buf[1000];  // 單詞的緩衝區
    input = fopen(argv[1], "r+");
    output = fopen(argv[2], "w+");
    sscanf(argv[3], "%ld", &num);

    
    int buflen = 0;  // 緩衝區中已經寫入的字符數
    int linePos = 0;  // 輸出文件中當前行中已經寫入的字符數
    int inputInt = 0;
    unsigned char inputChar = 0;
    if (num == 0){
        setvbuf(input, NULL, _IONBF, 1024);  //unbuf
        setvbuf(output, NULL, _IONBF, 1024);
    }
    else if (num == -1){
        setvbuf(input, NULL, _IOLBF, 1024);  //linebuf
        setvbuf(output, NULL, _IOLBF, 1024);  
    }
    else{
        setvbuf(input, NULL, _IOFBF, num); //fullybuf
        setvbuf(output, NULL, _IOFBF, num);
    }

    memset(word_buf, '\0', sizeof(word_buf)); //初始化
    
    while ((inputInt = getc(input)) != EOF){

        inputChar = (unsigned char)inputInt;  // 將讀取到的整數轉換為 unsigned char 型別

        if(inputChar != ' ') word_buf[buflen++] = inputChar;

        if(isspace(inputChar) && buflen != 0){
            if (linePos + buflen > 80){  // 如果單詞緩衝區中的內容加上當前行已經寫入的內容超過了 80 個字符，則在輸出文件中插入一個換行符
                fprintf(output, "%s", "\n");
                linePos = 0;
            }

            if (linePos != 0) fprintf(output, "%c",' ');

            fprintf(output, "%s", word_buf);
            linePos += buflen + 1;

            if (inputChar == '\n') linePos=0; //避免開頭多印空格

            memset(word_buf, '\0', sizeof(word_buf));
            buflen = 0;  // 清空單詞緩衝區
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}
