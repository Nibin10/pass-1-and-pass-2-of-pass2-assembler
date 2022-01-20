#include<stdio.h>
#include<string.h>
void main()
{
    char add[10],label[10],opcode[10],operand[10],len[10],code[10],mnemonic[10],lab[10],loc[10],start[10];
    int length;
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("out.txt","r");
    fp2=fopen("length.txt","r");
    fp3=fopen("optab.txt","r");
    fp4=fopen("symtbl.txt","r");

    fscanf(fp1,"%s\t%s\t%s\t%s",add,label,opcode,operand);

    if(strcmp(opcode,"START")==0)
    {
        strcpy(start,operand);
        fscanf(fp2,"%s",len);
    }
    printf("H^%s^00%s^00%s\nT^00%s",label,start,len,start);
    fscanf(fp1,"%s\t%s\t%s\t%s",add,label,opcode,operand);
    while(strcmp(opcode,"END")!=0)
    {
        rewind(fp3);
        fscanf(fp3,"%s\t%s",code,mnemonic);
        while(!feof(fp3))
        {
            if(strcmp(opcode,code)==0)
            {
                rewind(fp4);
                fscanf(fp4,"%s\t%s",lab,loc);
                while(!feof(fp4))
                {
                if(strcmp(operand,lab)==0)
                    {
                        printf("^%s%s",mnemonic,loc);
                        break;
                    }
                else
                    {
                    fscanf(fp4,"%s\t%s",lab,loc);
                    }
                }
                break;
            }
            else
            {
                fscanf(fp3,"%s\t%s",code,mnemonic);
            }
        }
        fscanf(fp1,"%s\t%s\t%s\t%s",add,label,opcode,operand); 
        if((strcmp(opcode,"BYTE"))==0||(strcmp(opcode,"WORD")==0))
        {
            if(strcmp(opcode,"WORD")==0)
            {
                printf("^00000%s",operand);
            }
            else
            {
                printf("^");
                length=strlen(operand);
                for(int i=2;i<length-1;i++)
                {
                    printf("%d",operand[i]);
                }
            }
        }
    }
    printf("\nE^00%s",start);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}