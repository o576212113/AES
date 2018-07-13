#pragma once
#include "Command.h"

class CMyAesDec
{
public:
    CMyAesDec();
    virtual ~CMyAesDec();
public:
    void DecCode(TagDecCodeInfo &decCodeInfo, char* pPlainText);  //解密
    void DecFile(TagDecCodeInfo &decCodeInfo, TagFileInfo &fileInfo);   //解密文件
    void XorIv(char *pIv, char* pStr);               //与IV异或操作
    void KeyExpand(char *pKey);                      //密钥扩展   
    void DwordToArray(DWORD dwKey, DWORD dwArray[4]);//将一个Dword 拆分成四个Dword
    void LeftMove(DWORD dwArray[4], int nStep);      //左移
    void ConvertToArray(char *pStr, DWORD pEnTextArray[4][4]);  //将密文16个字节一组的密文存成4*4的矩阵数组
    void RoundKeyAdd(DWORD pEnTextArray[4][4], int nRound);     //轮钥密加
    void ReMoveRow(DWORD pEnTextArray[4][4]);                   //行移位
    void RightMove(DWORD dwArray[4], int nStep);                //右移
    void ReByteChange(DWORD pEnTextArray[4][4]);                //逆字节代换
    void ReColConfusion(DWORD pEnTextArray[4][4]);              //逆列混淆
    void ArrayToStr(DWORD plainTextArray[4][4], char* pEnStr);  //将4*4的矩阵明文转换回字符串
    int GetLeftMoveIndex(int Index);                 //获取左移后的下标
    int ArrayToDword(DWORD dwArray[4]);              //将四个Dword 合成一个Dword
    int GetRightMoveIndex(int Index);                //获取左移后的下标
    DWORD DwordEncrypt(DWORD dwValue, int nRound);   //对一个字进行加密
    DWORD FromSboxReplace(DWORD dwValue);            //从S盒内获取对应值
    DWORD FromReSboxReplace(DWORD dwValue);          //从逆S盒内获取对应值
    DWORD GFMulTwo(DWORD dwValue);                   //乘法2
    DWORD GFMulFour(DWORD dwValue);             
    DWORD GFMulEight(DWORD dwValue);                
    DWORD GFMul(DWORD MatrixValue, DWORD dwValue);   //乘法拆分
    DWORD MyReadFile(HANDLE hFile, DWORD dwCount, char *szBuffToRead);  //读文件
    DWORD MyWriteFile(HANDLE hFile, char* szBuffToWrite);               //写文件
    

private:
    DWORD m_dwKeyArray[KEYARRAYCOUNT];             //扩展密钥
    static const int m_ReSbox[16][16];             //逆S盒
    static const int m_Sbox[16][16];               //S盒
    static const int m_Rcon[10];                   //轮常量
    static const int m_ReFixedMatrix[4][4];        //逆固定矩阵
};

