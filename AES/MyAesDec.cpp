#include "stdafx.h"
#include "MyAesDec.h"

const int CMyAesDec::m_Sbox[16][16] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };


const int CMyAesDec::m_ReSbox[16][16] = { 
0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

const int CMyAesDec::m_Rcon[10] = {
    0x01000000, 0x02000000,
    0x04000000, 0x08000000,
    0x10000000, 0x20000000,
    0x40000000, 0x80000000,
    0x1b000000, 0x36000000 };

const int CMyAesDec::m_ReFixedMatrix[4][4] = {
0xe, 0xb, 0xd, 0x9,
0x9, 0xe, 0xb, 0xd,
0xd, 0x9, 0xe, 0xb,
0xb, 0xd, 0x9, 0xe };

CMyAesDec::CMyAesDec()
{
}


CMyAesDec::~CMyAesDec()
{

}

//解密
void CMyAesDec::DecCode(TagDecCodeInfo &decCodeInfo, char* pPlainText)
{
    KeyExpand(decCodeInfo.pKey);    //扩展密钥

    DWORD pEnTextArray[4][4] = { 0 };

    char szCurIv[32] = { 0 };
    memmove(szCurIv, decCodeInfo.pIv, 16);

    for (int i = 0; i < decCodeInfo.pEnTextLength; i += 16)
    {
        //将1组16字节的密文转换成4*4数组
        ConvertToArray(decCodeInfo.pEnText + i, pEnTextArray);

        //第10次的轮钥密加
        RoundKeyAdd(pEnTextArray, 10);

        for (int j = 9; j > 0; j--)
        {
            //逆行移位
            ReMoveRow(pEnTextArray);

            //逆字节代换
            ReByteChange(pEnTextArray);

            //轮密钥加
            RoundKeyAdd(pEnTextArray, j);

            //逆列混淆
            ReColConfusion(pEnTextArray);
        }

        //最后一轮操作
        //逆行移位
        ReMoveRow(pEnTextArray);

        //逆字节代换
        ReByteChange(pEnTextArray);

        //逆轮密钥加
        RoundKeyAdd(pEnTextArray, 0);

        //将4*4的密文矩阵转换回字符串
        ArrayToStr(pEnTextArray, pPlainText + i);
        
        //块解密后与IV异或得到明文
        XorIv(szCurIv, pPlainText + i);

        //下一轮的IV是当前的密文
        memmove(szCurIv, decCodeInfo.pEnText + i, 16);
    }
}

//解密文件
void CMyAesDec::DecFile(TagDecCodeInfo &decCodeInfo, TagFileInfo &fileInfo)
{
    //获取文件大小
    DWORD dwFileSize = GetFileSize(fileInfo.hSrcFile, NULL);

    KeyExpand(decCodeInfo.pKey);    //扩展密钥

    DWORD pEnTextArray[4][4] = { 0 };
    char szCurIv[32] = { 0 };
    char szTempIv[32] = { 0 };
    memmove(szCurIv, decCodeInfo.pIv, 16);

    for (int i = 0; i < dwFileSize; i += 16)
    {
        //从文件读16个字节的内容
        TCHAR szBuffToRead[MAXBYTE] = { 0 };
        MyReadFile(fileInfo.hSrcFile, 16, szBuffToRead);

        //记录下密文
        memmove(szTempIv, szBuffToRead, 16);

        //将1组16字节的密文转换成4*4数组
        ConvertToArray(szBuffToRead, pEnTextArray);

        //第10次的轮钥密加
        RoundKeyAdd(pEnTextArray, 10);

        for (int j = 9; j > 0; j--)
        {
            //逆行移位
            ReMoveRow(pEnTextArray);

            //逆字节代换
            ReByteChange(pEnTextArray);

            //轮密钥加
            RoundKeyAdd(pEnTextArray, j);

            //逆列混淆
            ReColConfusion(pEnTextArray);
        }

        //最后一轮操作
        //逆行移位
        ReMoveRow(pEnTextArray);

        //逆字节代换
        ReByteChange(pEnTextArray);

        //逆轮密钥加
        RoundKeyAdd(pEnTextArray, 0);

        //将4*4的密文矩阵转换回字符串
        ArrayToStr(pEnTextArray, szBuffToRead);

        //块解密后与IV异或得到明文
        XorIv(szCurIv, szBuffToRead);

        //写入文件
        MyWriteFile(fileInfo.hTagFile, szBuffToRead);

        //下一轮的IV是当前的密文
        memmove(szCurIv, szTempIv, 16);
    }
}


//与IV异或操作
void CMyAesDec::XorIv(char *pIv, char* pStr)
{
    for (int i = 0; i < 16; i++)
    {
        pStr[i] = pIv[i] ^ pStr[i];
    }
}

//密钥扩展   
void CMyAesDec::KeyExpand(char *pKey)
{
    //先取出前初始密钥
    for (int i = 0; i < 4; i++)
    {
        m_dwKeyArray[i] = *(DWORD*)(pKey + i * 4);
    }

    //生成另外40组
    int j = 0;
    for (int i = 4; i < 44; i++)
    {
        if (i % 4 != 0)     //如果不是4的倍数
        {
            //W[i]=W[i-4]⨁W[i-1] 
            m_dwKeyArray[i] = m_dwKeyArray[i - 4] ^ m_dwKeyArray[i - 1];
        }
        else
        {
            m_dwKeyArray[i] = m_dwKeyArray[i - 4] ^ DwordEncrypt(m_dwKeyArray[i - 1], j);
            j++;
        }
    }
}

//对扩展密钥中轮数是4的倍数的值进行三步加密操作
//1.字循环 {a1,a2,a3,a4} 左移1个字节 {a2,a3,a4,a1}
//2.字节代换
//3.轮常量异或
DWORD CMyAesDec::DwordEncrypt(DWORD dwValue, int nRound)
{
    //字循环 {a1,a2,a3,a4} 左移1个字节 {a2,a3,a4,a1}
    //先将一个DWORD拆分成四个DWORD
    DWORD dwArray[4] = { 0 };
    DwordToArray(dwValue, dwArray);

    //左移1个字节
    LeftMove(dwArray, 1);

    //字节代换 字节的高四位作为行,低四位作为列 通过下标在S盒内取值替换
    for (int i = 0; i < 4; i++)
    {
        dwArray[i] = FromSboxReplace(dwArray[i]);
    }

    //将四个DWORD合成一个DWORD
    DWORD dwRet = ArrayToDword(dwArray);

    //轮常量异或
    dwRet = dwRet ^ m_Rcon[nRound];

    return dwRet;
}

//将一个Dword 拆分成四个Dword
void CMyAesDec::DwordToArray(DWORD dwKey, DWORD dwArray[4])
{
    dwArray[0] = (dwKey >> 24) & 0x000000ff;
    dwArray[1] = (dwKey >> 16) & 0x000000ff;
    dwArray[2] = (dwKey >> 8) & 0x000000ff;
    dwArray[3] = dwKey & 0x000000ff;
}

//左移
void CMyAesDec::LeftMove(DWORD dwArray[4], int nStep)
{
    if (nStep <= 0)
    {
        return;
    }

    int dwTempArray[4] = { 0 };
    for (int i = 0; i < 4; i++)
    {
        dwTempArray[i] = dwArray[i];
    }

    // 1 2 3 4      2 3 4 1
    for (int i = 0; i < 4; i++)
    {
        int Dvalue = i - nStep;
        if (Dvalue >= 0)
        {
            dwArray[Dvalue] = dwTempArray[i];
        }
        else
        {
            int nIndex = GetLeftMoveIndex(Dvalue);
            dwArray[nIndex] = dwTempArray[i];
        }
    }
}

//获取左移后的下标
int CMyAesDec::GetLeftMoveIndex(int Index)
{
    int nRet = -1;
    switch (Index)
    {
    case -1:
        nRet = 3;
        break;
    case -2:
        nRet = 2;
        break;
    case -3:
        nRet = 1;
        break;
    default:
        break;
    }
    return nRet;
}

//从S盒内获取对应值
DWORD CMyAesDec::FromSboxReplace(DWORD dwValue)
{
    int nRow = (dwValue & 0x000000f0) >> 4;     //高四位（是一个字节的）
    int nCol = dwValue & 0x0000000f;            //低四位
    return m_Sbox[nRow][nCol];
}
//从逆S盒内获取对应值
DWORD CMyAesDec::FromReSboxReplace(DWORD dwValue)
{
    int nRow = (dwValue & 0x000000f0) >> 4;     //高四位（是一个字节的）
    int nCol = dwValue & 0x0000000f;            //低四位
    return m_ReSbox[nRow][nCol];
}

//将四个Dword 合成一个Dword
int CMyAesDec::ArrayToDword(DWORD dwArray[4])
{
    DWORD dwN1 = dwArray[0] << 24;
    DWORD dwN2 = dwArray[1] << 16;
    DWORD dwN3 = dwArray[2] << 8;
    DWORD dwN4 = dwArray[3];
    DWORD dwRet = dwN1 | dwN2 | dwN3 | dwN4;
    return dwRet;
}

//将密文16个字节一组的密文存成4*4的矩阵数组
void CMyAesDec::ConvertToArray(char *pStr, DWORD pEnTextArray[4][4])
{
    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            pEnTextArray[j][i] = ((BYTE)*(pStr + k));
            k++;
        }
    }
}

//轮钥密加
void CMyAesDec::RoundKeyAdd(DWORD pEnTextArray[4][4], int nRound)
{
    DWORD dwArray[4] = { 0 };

    for (int i = 0; i < 4; i++)
    {
        //拆分
        DwordToArray(m_dwKeyArray[nRound * 4 + i], dwArray);

        for (int j = 0; j < 4; j++)
        {
            //矩阵中每一字节异或
            pEnTextArray[j][i] = pEnTextArray[j][i] ^ dwArray[j];
        }
    }
}

//逆行移位
void CMyAesDec::ReMoveRow(DWORD pEnTextArray[4][4])
{
    DWORD dwN1[4] = { 0 };
    DWORD dwN2[4] = { 0 };
    DWORD dwN3[4] = { 0 };

    //先将矩阵中1,2,3行分别取出
    for (int i = 0; i < 4; i++)
    {
        dwN1[i] = pEnTextArray[1][i];
        dwN2[i] = pEnTextArray[2][i];
        dwN3[i] = pEnTextArray[3][i];
    }

    //每一行单独右移操作
    RightMove(dwN1, 1);
    RightMove(dwN2, 2);
    RightMove(dwN3, 3);

    //每一行右移操作后赋值回矩阵
    for (int i = 0; i < 4; i++)
    {
        pEnTextArray[1][i] = dwN1[i];
        pEnTextArray[2][i] = dwN2[i];
        pEnTextArray[3][i] = dwN3[i];
    }
}

//右移
void CMyAesDec::RightMove(DWORD dwArray[4], int nStep)
{
    if (nStep <= 0)
    {
        return;
    }

    int dwTempArray[4] = { 0 };
    for (int i = 0; i < 4; i++)
    {
        dwTempArray[i] = dwArray[i];
    }

    // 1 2 3 4      4 1 2 3
    for (int i = 0; i < 4; i++)
    {
        int Dvalue = i + nStep;

        if (Dvalue > 3 )
        {
            int nIndex = GetRightMoveIndex(Dvalue);
            dwArray[nIndex] = dwTempArray[i];
        }
        else
        {
            dwArray[Dvalue] = dwTempArray[i];
        }
    }
}

//获取左移后的下标
int CMyAesDec::GetRightMoveIndex(int Index)
{
    int nRet = -1;
    switch (Index)
    {
    case 4:
        nRet = 0;
        break;
    case 5:
        nRet = 1;
        break;
    case 6:
        nRet = 2;
        break;
    default:
        break;
    }
    return nRet;
}

//逆字节代换
void CMyAesDec::ReByteChange(DWORD pEnTextArray[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            pEnTextArray[i][j] = FromReSboxReplace(pEnTextArray[i][j]);
        }
    }
}

//逆列混淆
void CMyAesDec::ReColConfusion(DWORD pEnTextArray[4][4])
{
    DWORD dwTempArray[4][4] = { 0 };
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            dwTempArray[i][j] = pEnTextArray[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            pEnTextArray[i][j] = GFMul(m_ReFixedMatrix[i][0], dwTempArray[0][j]) ^ GFMul(m_ReFixedMatrix[i][1], dwTempArray[1][j]) ^
                                 GFMul(m_ReFixedMatrix[i][2], dwTempArray[2][j]) ^ GFMul(m_ReFixedMatrix[i][3], dwTempArray[3][j]);
        }
    }
}

//乘法2
DWORD CMyAesDec::GFMulTwo(DWORD dwValue)
{
    DWORD dwRet = dwValue << 1;     //左移1位 等同域上的乘法*2

    if ((dwRet & 0x00000100) != 0)               //判断溢出
    {
        dwRet = dwRet & 0x000000ff;
        dwRet = dwRet ^ 0x1b;
    }
    return dwRet;
}

DWORD CMyAesDec::GFMulFour(DWORD dwValue)
{
    return  GFMulTwo(GFMulTwo(dwValue));
}

DWORD CMyAesDec::GFMulEight(DWORD dwValue)
{
    return  GFMulTwo(GFMulFour(dwValue));
}

//乘法拆分
DWORD CMyAesDec::GFMul(DWORD MatrixValue, DWORD dwValue)
{
    DWORD dwRet = 0;
    switch (MatrixValue)
    {
    case 1:
        dwRet = dwValue;
        break;
    case 2:
        dwRet = GFMulTwo(dwValue);
        break;
    case 3:
        dwRet = GFMulTwo(dwValue) ^ dwValue;
        break;
    case 9:
        dwRet = GFMulEight(dwValue) ^ dwValue;
        break;
    case 11:
        dwRet = GFMulEight(dwValue) ^ dwValue ^ GFMulTwo(dwValue);
        break;
    case 12:
        dwRet = GFMulEight(dwValue) ^ GFMulFour(dwValue);
        break;
    case 13:
        dwRet = GFMulEight(dwValue) ^ GFMulFour(dwValue) ^ dwValue;
        break;
    case 14:
        dwRet = GFMulEight(dwValue) ^ GFMulFour(dwValue) ^ GFMulTwo(dwValue);
        break;
    default:
        break;
    }

    return dwRet;
}

//将4*4的矩阵明文转换回字符串
void CMyAesDec::ArrayToStr(DWORD plainTextArray[4][4], char* pEnStr)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            *pEnStr++ = plainTextArray[j][i];
        }
    }
}


//读文件
DWORD CMyAesDec::MyReadFile(HANDLE hFile, DWORD dwCount, char *szBuffToRead)
{
    DWORD dwBytesToRead = 0;
    BOOL bSrcRet = ReadFile(hFile, szBuffToRead, 16, &dwBytesToRead, NULL);
    if (!bSrcRet)
    {
        AfxMessageBox(_T("读取文件失败"));
    }

    return dwBytesToRead;
}

//写文件
DWORD CMyAesDec::MyWriteFile(HANDLE hFile, char* szBuffToWrite)
{
    DWORD dwBytesToWrite = 0;
    BOOL bTagRet = WriteFile(hFile, szBuffToWrite, strlen(szBuffToWrite), &dwBytesToWrite, NULL);
    if (!bTagRet)
    {
        AfxMessageBox(_T("写入文件失败"));
        return 0;
    }

    return dwBytesToWrite;
}