#pragma once
#include "Command.h"

class CMyAesDec
{
public:
    CMyAesDec();
    virtual ~CMyAesDec();
public:
    void DecCode(TagDecCodeInfo &decCodeInfo, char* pPlainText);  //����
    void DecFile(TagDecCodeInfo &decCodeInfo, TagFileInfo &fileInfo);   //�����ļ�
    void XorIv(char *pIv, char* pStr);               //��IV������
    void KeyExpand(char *pKey);                      //��Կ��չ   
    void DwordToArray(DWORD dwKey, DWORD dwArray[4]);//��һ��Dword ��ֳ��ĸ�Dword
    void LeftMove(DWORD dwArray[4], int nStep);      //����
    void ConvertToArray(char *pStr, DWORD pEnTextArray[4][4]);  //������16���ֽ�һ������Ĵ��4*4�ľ�������
    void RoundKeyAdd(DWORD pEnTextArray[4][4], int nRound);     //��Կ�ܼ�
    void ReMoveRow(DWORD pEnTextArray[4][4]);                   //����λ
    void RightMove(DWORD dwArray[4], int nStep);                //����
    void ReByteChange(DWORD pEnTextArray[4][4]);                //���ֽڴ���
    void ReColConfusion(DWORD pEnTextArray[4][4]);              //���л���
    void ArrayToStr(DWORD plainTextArray[4][4], char* pEnStr);  //��4*4�ľ�������ת�����ַ���
    int GetLeftMoveIndex(int Index);                 //��ȡ���ƺ���±�
    int ArrayToDword(DWORD dwArray[4]);              //���ĸ�Dword �ϳ�һ��Dword
    int GetRightMoveIndex(int Index);                //��ȡ���ƺ���±�
    DWORD DwordEncrypt(DWORD dwValue, int nRound);   //��һ���ֽ��м���
    DWORD FromSboxReplace(DWORD dwValue);            //��S���ڻ�ȡ��Ӧֵ
    DWORD FromReSboxReplace(DWORD dwValue);          //����S���ڻ�ȡ��Ӧֵ
    DWORD GFMulTwo(DWORD dwValue);                   //�˷�2
    DWORD GFMulFour(DWORD dwValue);             
    DWORD GFMulEight(DWORD dwValue);                
    DWORD GFMul(DWORD MatrixValue, DWORD dwValue);   //�˷����
    DWORD MyReadFile(HANDLE hFile, DWORD dwCount, char *szBuffToRead);  //���ļ�
    DWORD MyWriteFile(HANDLE hFile, char* szBuffToWrite);               //д�ļ�
    

private:
    DWORD m_dwKeyArray[KEYARRAYCOUNT];             //��չ��Կ
    static const int m_ReSbox[16][16];             //��S��
    static const int m_Sbox[16][16];               //S��
    static const int m_Rcon[10];                   //�ֳ���
    static const int m_ReFixedMatrix[4][4];        //��̶�����
};

