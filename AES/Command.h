#pragma once
#define KEYARRAYCOUNT 44

//base64编码表
extern const char *base64char;

//base64编码
void Base64_EnStr(const char *base64char, unsigned  char *pData, int nDataLen, unsigned char *pRevData);   

//base64解码
DWORD Base64_DecStr(const char *base64char, char *pEnData, int nEnDataLen, unsigned char *pRevData);

int GetBase64Index(const char *base64char, char cChar);

//加密所需参数
struct TagEnCodeInfo
{
    char* pPlainText;
    int nPlainTextLength;
    char* pKey;
    int nKeyLength;
    char* pIv;
};


//解密所需参数
struct TagDecCodeInfo
{
    char* pEnText;
    int pEnTextLength;
    char* pKey;
    int nKeyLength;
    char* pIv;
};

struct TagFileInfo
{
    HANDLE hTagFile;
    HANDLE hSrcFile;
};