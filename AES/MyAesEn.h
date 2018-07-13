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
    int GetLeftMoveIndex(int nIndex);                        //��ȡ���ƺ���±�
    int ArrayToDword(DWORD dwArray[4]);                      //���ĸ�Dword �ϳ�һ��Dword
    DWORD EnCode(TagEnCodeInfo &enCodeInfo, char* pEnText);  //����
    void EnFile(TagEnCodeInfo &enCodeInfo, TagFileInfo &fileInfo); //�����ļ�
    void XorIv(char *pIv, char* pStr);                     //��IV������
    void KeyExpand(char *pKey);                            //��Կ��չ   
    void ColConfusion(DWORD plainTextArray[4][4]);         //�л���
    void DwordToArray(DWORD dwKey,DWORD dwArray[4]);       //��һ��Dword ��ֳ��ĸ�Dword
    void LeftMove(DWORD dwArray[4], int nStep);            //����
    void ConvertToArray(char *pStr, DWORD plainTextArray[4][4]);    //������16���ֽ�һ������Ĵ��4*4�ľ�������
    void ArrayToStr(DWORD plainTextArray[4][4], char* pEnStr);      //��4*4�ľ�������ת�����ַ���
    void RoundKeyAdd(DWORD plainTextArray[4][4], int nRound);       //��Կ�ܼ�
    void ByteChange(DWORD plainTextArray[4][4]);                    //�ֽڴ���
    void MoveRow(DWORD plainTextArray[4][4]);                       //����λ
    DWORD FromSboxReplace(DWORD dwValue);                           //��S���ڻ�ȡ��Ӧֵ
    DWORD DwordEncrypt(DWORD dwValue, int nRound);                  //��һ���ֽ��м���
    DWORD GFMul(DWORD MatrixValue, DWORD dwValue);                  //�˷����
    DWORD GFMulTwo(DWORD dwValue);                                  //�˷�2
    char* ZeroPadding(char* pPlainText, int nPlainTextLength);      //�ֽڲ���
    DWORD MyReadFile(HANDLE hFile, DWORD dwCount, char *szBuffToRead);    //���ļ�
    DWORD MyWriteFile(HANDLE hFile, char* szBuffToWrite);                 //д�ļ�
 
private:
    DWORD m_dwKeyArray[KEYARRAYCOUNT];             //��չ��Կ
    static const int m_Sbox[16][16];               //S��
    static const int m_Rcon[10];                   //�ֳ���
    static const int m_FixedMatrix[4][4];          //�̶�����
};

