#pragma once
#include "Command.h"

extern const char *base64char;

class CMyAesEn
{
public:
    CMyAesEn(char* pPlainText, char* m_pKey);
    CMyAesEn();
    virtual ~CMyAesEn();
public:
    int GetLeftMoveIndex(int nIndex);                        //获取左移后的下标
    int ArrayToDword(DWORD dwArray[4]);                      //将四个Dword 合成一个Dword
    DWORD EnCode(TagEnCodeInfo &enCodeInfo, char* pEnText);  //加密
    void EnFile(TagEnCodeInfo &enCodeInfo, TagFileInfo &fileInfo); //加密文件
    void XorIv(char *pIv, char* pStr);                     //与IV异或操作
    void KeyExpand(char *pKey);                            //密钥扩展   
    void ColConfusion(DWORD plainTextArray[4][4]);         //列混淆
    void DwordToArray(DWORD dwKey,DWORD dwArray[4]);       //将一个Dword 拆分成四个Dword
    void LeftMove(DWORD dwArray[4], int nStep);            //左移
    void ConvertToArray(char *pStr, DWORD plainTextArray[4][4]);    //将明文16个字节一组的明文存成4*4的矩阵数组
    void ArrayToStr(DWORD plainTextArray[4][4], char* pEnStr);      //将4*4的矩阵密文转换会字符串
    void RoundKeyAdd(DWORD plainTextArray[4][4], int nRound);       //轮钥密加
    void ByteChange(DWORD plainTextArray[4][4]);                    //字节代换
    void MoveRow(DWORD plainTextArray[4][4]);                       //行移位
    DWORD FromSboxReplace(DWORD dwValue);                           //从S盒内获取对应值
    DWORD DwordEncrypt(DWORD dwValue, int nRound);                  //对一个字进行加密
    DWORD GFMul(DWORD MatrixValue, DWORD dwValue);                  //乘法拆分
    DWORD GFMulTwo(DWORD dwValue);                                  //乘法2
    char* ZeroPadding(char* pPlainText, int nPlainTextLength);      //字节补齐
    DWORD MyReadFile(HANDLE hFile, DWORD dwCount, char *szBuffToRead);    //读文件
    DWORD MyWriteFile(HANDLE hFile, char* szBuffToWrite);                 //写文件
 
private:
    DWORD m_dwKeyArray[KEYARRAYCOUNT];             //扩展密钥
    static const int m_Sbox[16][16];               //S盒
    static const int m_Rcon[10];                   //轮常量
    static const int m_FixedMatrix[4][4];          //固定矩阵
};

