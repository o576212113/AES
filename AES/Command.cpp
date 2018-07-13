#include "stdafx.h"
#include "Command.h"
#include <cstringt.h>

const char *base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//base64编码
void Base64_EnStr(const char *base64char, unsigned  char *pData, int nDataLen, unsigned char *pRevData)
{
    int nRemainder = 0;
    int j = 0;
    for (int i = 0; i < nDataLen; i++, j++)
    {
        nRemainder = i % 3;
        switch (nRemainder)
        {
        case 0:
        {
                  //第一个base64字符
                  BYTE n = pData[i] >> 2;               //第一个8位 右移2位 取第一个字符
                  pRevData[j] = base64char[n];
                  break;
        }
        case 1:
        {
                  //第二个base64字符
                  BYTE n1 = pData[i - 1] & 3;           //第一个8位&上0x00000011 取第一个8位的后2位
                  BYTE n2 = n1 << 6;                    //将取出的后2位左移6位变最高2位
                  BYTE n3 = pData[i] >> 2;              //第二个8位右移2位
                  BYTE n4 = n3 | n2;
                  BYTE n5 = n4 >> 2;
                  pRevData[j] = base64char[n5];
                  break;
        }
        case 2:
        {
                  //第三个base64字符
                  BYTE n1 = pData[i - 1] << 4;          //第二个八位左移四位
                  BYTE n2 = pData[i] >> 4;              //第三个八位右移四位
                  BYTE n3 = n1 | n2;
                  BYTE n4 = n3 >> 2;
                  pRevData[j] = base64char[n4];

                  //第四个base64字符
                  BYTE n5 = pData[i] & 0x3f;           //第三个八位&上00111111
                  pRevData[++j] = base64char[n5];
                  break;
        }
        default:
            break;
        }
    }

    //如果等于0 代表是多出1个字符，并且还要取3个base64编码符号，其中后两个base64编码符号为"="
    if (nRemainder == 0)
    {
        BYTE n1 = pData[nDataLen - 1] & 3;
        BYTE n2 = n1 << 4;
        pRevData[j] = base64char[n2];
        pRevData[++j] = '=';
        pRevData[++j] = '=';
    }
    //如果等于1 代表是多出2个字符，并且还要取2个base64编码符号，其中后1个base64编码符号为"="
    else if (nRemainder == 1)
    {
        BYTE n1 = pData[nDataLen - 1] & 0xf;
        BYTE n2 = n1 << 2;
        pRevData[j] = base64char[n2];
        pRevData[++j] = '=';
    }
    pRevData[j + 1] = '\0';
}


//base64解码
DWORD Base64_DecStr(const char *base64char, char *pEnData, int nEnDataLen, unsigned char *pRevData)
{
    int nRemainder = 0;
    int j = 0;
    for (int i = 0; i < nEnDataLen; i++)
    {
        nRemainder = i % 4;

        if (pEnData[i] == '=')
        {
            continue;
        }
        switch (nRemainder)
        {
        case 0:
            break;
        case 1:
        {
                  BYTE n1 = GetBase64Index(base64char, pEnData[i - 1]);
                  BYTE n2 = GetBase64Index(base64char, pEnData[i]);
                  BYTE b1 = n1 << 2;
                  BYTE b2 = n2 >> 4;
                  BYTE b3 = b1 | b2;
                  pRevData[j++] = b3;
                  break;
        }
        case 2:
        {
                  BYTE n1 = GetBase64Index(base64char, pEnData[i - 1]);
                  BYTE n2 = GetBase64Index(base64char, pEnData[i]);
                  BYTE b1 = n1 << 4;
                  BYTE b2 = n2 >> 2;
                  BYTE b3 = b1 | b2;
                  pRevData[j++] = b3;
                  break;
        }
        case 3:
        {
                  BYTE n1 = GetBase64Index(base64char, pEnData[i - 1]);
                  BYTE n2 = GetBase64Index(base64char, pEnData[i]);
                  BYTE b1 = n1 << 6;
                  BYTE b3 = b1 | n2;
                  pRevData[j++] = b3;
                  break;
        }
        default:
            break;
        }
    }
    pRevData[j] = '\0';
    return j;
}

int GetBase64Index(const char *base64char, char cChar)
{
    for (int i = 0; i < strlen(base64char); i++)
    {
        if (base64char[i] == cChar)
        {
            return i;
        }
    }
    return -1;
}

