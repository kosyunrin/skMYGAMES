#pragma once
#include<string>
#include <locale>
#include <codecvt> 
#include <iostream>
#include<random>
#include<iomanip>
#include <sstream>
#include"renderer.h"
#define PIx 3.1415926
class Tool
{
public:
	static int Distance(XMFLOAT3 v1, XMFLOAT3 v2)
	{
		int d = sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y) + (v1.z - v2.z)*(v1.z - v2.z));
		return d;
	}
	static float Distance_float(XMFLOAT3 v1, XMFLOAT3 v2)
	{
		float d = sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y) + (v1.z - v2.z)*(v1.z - v2.z));
		return d;
	}
	static float Get_Ht(float looger, float deg)
	{
		float H;
		H = sinf(deg)*looger;
		return H;
	}
	static float GET_ANGLE(XMVECTOR p1, XMVECTOR p2)
	{
		return XMVectorGetY(XMVector3Cross(p1, p2));
	}
	static float GET_ANGLE_DOT(XMVECTOR p1, XMVECTOR p2)
	{
		return XMVectorGetY(XMVector3Dot(p1, p2));
	}
	static double Random(float p1, float p2)
	{
		std::default_random_engine E;
		std::uniform_real_distribution<double> u(p1, p2);
		return u(E);
	}
	static int RandomInt(int a, int b)
	{
		return (rand() % (b - a)) + a;
	}
	static float KeepDecimal(long num,int bits)
	{
		
		std::stringstream ss;
		ss << std::fixed << std::setprecision(bits) << num;
		float f;
		ss >> f;

		return f;
	}
	static double KeepDecimal2(_In_ double dSrc, _In_ int iBit)
	{
		double retVal = 0.0;
		int  intTmp = 0;


		// 若保留小数位数不正确
		if (iBit < 0) return 0;
		//=-1
		if (dSrc < 0)
		{
			// 首先转为正数
			dSrc *= -1;

			intTmp = (int)((dSrc + 0.5 / pow(10.0, iBit)) * pow(10.0, iBit));
			retVal = (double)intTmp / pow(10.0, iBit);

			// 再转为 负数
			retVal *= -1;
		}
		else
		{
			intTmp = (int)((dSrc + 0.5 / pow(10.0, iBit)) * pow(10.0, iBit));
			retVal = (double)intTmp / pow(10.0, iBit);
		}

		return retVal;
	}
	static XMVECTOR GetP1ToP2(XMFLOAT3 p1, XMFLOAT3 p2)
	{
		XMVECTOR p11 = XMLoadFloat3(&p1);
		XMVECTOR p22 = XMLoadFloat3(&p2);
		return XMVector3Normalize(p11 - p22);
	}
	static void TextBegain()
	{
		CRenderer::spritebich->Begin();
	}
	static void TextDraw(STRINGDRAW string)
	{
		CRenderer::spritefont->DrawString(CRenderer::spritebich.get(), string.Text.c_str(), string.Pos, string.Color, string.RotSpeed, string.RotPoint, string.Scale);
	}
	static void TextEnd()
	{
		CRenderer::spritebich->End();
		CRenderer::DrawStringBack();
	}

	static float GetDegForP1ToP2(XMFLOAT3 p1, XMFLOAT3 p2,XMVECTOR faceDir)
	{
		XMVECTOR p11 = XMLoadFloat3(&p1);
		XMVECTOR p22 = XMLoadFloat3(&p2);
		XMVECTOR dir = XMVector3Normalize(p11 - p22);
		float deg = XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, dir));
		Tool::GET_ANGLE(dir, faceDir) > 0.0f ? deg = -deg : deg = deg;
		return  deg;
	}
	static float GetDegForP1ToP2(XMVECTOR dir, XMVECTOR faceDir)
	{
		float deg = XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, dir));
		Tool::GET_ANGLE(dir, faceDir) > 0.0f ? deg = -deg : deg = deg;
		return  deg;
	}
	static void BlendRunUp(float& outblend, float dt, float speed)
	{
		if (outblend < 1.0f)
		{
			outblend += dt * speed;
		}
		else
		{
			outblend = 1.0f;
		}
	}
	static void BlendRunDown(float& outblend, float dt, float speed)
	{
		if (outblend > 0.0f)
		{
			outblend -= dt * speed;
		}
		else
		{
			outblend = 0.0f;
		}
	}
	static void DeBugMoveV3(XMFLOAT3& out)
	{
		out.x = CRenderer::Debug_move_v3[0];
		out.y = CRenderer::Debug_move_v3[1];
		out.z = CRenderer::Debug_move_v3[2];
	}
	static void DeBugMoveV3two(XMFLOAT3& out)
	{
		out.x = CRenderer::Debug_move_Rotation3[0];
		out.y = CRenderer::Debug_move_Rotation3[1];
		out.z = CRenderer::Debug_move_Rotation3[2];
	}
	static void DeBugMoveV2(XMFLOAT2& out)
	{
		out.x = CRenderer::Debug_move_v2[0];
		out.y = CRenderer::Debug_move_v2[1];
	}
	static XMVECTOR GetNowFaceDir(XMMATRIX rotmatrix)
	{
		XMVECTOR oldface = { 0.0f,0.0f,-1.0f,0.0f };
		return XMVector3TransformNormal(oldface, rotmatrix);
	}
	static XMVECTOR GetNowDir(XMMATRIX rotmatrix,XMVECTOR olddir)
	{
		return XMVector3TransformNormal(olddir, rotmatrix);
	}
	static XMVECTOR GetTransformCoord(XMMATRIX rotmatrix, XMVECTOR olddir)
	{
		return XMVector3TransformCoord(olddir, rotmatrix);
	}
	static void SetObjectRot(float& outY, XMFLOAT3 p1, XMFLOAT3 p2, XMVECTOR faceDir)
	{
		/*XMVECTOR p11 = XMLoadFloat3(&p1);
		XMVECTOR p22 = XMLoadFloat3(&p2);
		XMVECTOR dir = XMVector3Normalize(p11 - p22);
	   float Deg= XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, dir));
	   Tool::GET_ANGLE(dir, faceDir) > 0.0f ? outY = -Deg : outY = Deg;*/
	}
	static std::wstring StrToWtr(const std::string str)
	{
		std::string message;
		/*"asset/Onepiece/" +*/
	/*	if (str.length() > 30)
		{
			message = str.substr(25, str.length());
		}*/
		message =  str;
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
		//string→wstring
		std::wstring wsmessage = cv.from_bytes(message);
		std::wcout.imbue(std::locale(""));
		std::wcout << wsmessage << std::endl;
		return wsmessage;

	}
	//static void DistanceF(xmfloat3)
	//static void SetMAXMIN(MeshPart* m_meshPart,VERTEX_3D* ver,UINT size,UINT i,UINT m)
	//{
	//		XMFLOAT3 currentPos = ver[i].Position;
	//		if (m_meshPart[m].m_BoxPoint.Vmax.x <= currentPos.x)
	//			m_meshPart[m].m_BoxPoint.Vmax.x = currentPos.x;
	//		if (m_meshPart[m].m_BoxPoint.Vmax.y <= currentPos.y)
	//			m_meshPart[m].m_BoxPoint.Vmax.y = currentPos.y;
	//		if (m_meshPart[m].m_BoxPoint.Vmax.z <= currentPos.z)
	//			m_meshPart[m].m_BoxPoint.Vmax.z = currentPos.z;
	//		//			   m
	//		if (m_meshPart[m].m_BoxPoint.Vmin.x > currentPos.x)
	//			m_meshPart[m].m_BoxPoint.Vmin.x = currentPos.x;
	//		if (m_meshPart[m].m_BoxPoint.Vmin.y > currentPos.y)
	//			m_meshPart[m].m_BoxPoint.Vmin.y = currentPos.y;
	//		if (m_meshPart[m].m_BoxPoint.Vmin.z > currentPos.z)
	//			m_meshPart[m].m_BoxPoint.Vmin.z = currentPos.z;
	//}
	static XMFLOAT3 GET_MAX_VERTEX3(XMFLOAT3 currentPos, XMFLOAT3 outPos)
	{
			if (outPos.x <= currentPos.x)
				outPos.x = currentPos.x;
			if (outPos.y <= currentPos.y)
				outPos.y = currentPos.y;
			if (outPos.z <= currentPos.z)
				outPos.z = currentPos.z;
			return outPos;
	}
	static XMFLOAT3 GET_MIN_VERTEX3(XMFLOAT3 currentPos, XMFLOAT3 outPos)
	{
		if (outPos.x > currentPos.x)
			outPos.x = currentPos.x;
		if (outPos.y > currentPos.y)
			outPos.y = currentPos.y;
		if (outPos.z > currentPos.z)
			outPos.z = currentPos.z;
		return outPos;
	}
	static XMFLOAT3 Intersection_PlaneTo_ray(XMFLOAT3 origin, XMFLOAT3 direction)
	{
		XMFLOAT3 FXL = { 0.0f,1.0f,0.0f };//faxiangliang
		XMFLOAT3 a = { 0.0f,0.0f,10.0f };//pingmian lei yidian 
		//n.a
		float na = FXL.x*a.x + FXL.y*a.y + FXL.z*a.z;
		//n.d
		float nd= FXL.x*direction.x + FXL.y*direction.y + FXL.z*direction.z;
		//n*o
		float no = FXL.x*origin.x + FXL.y*origin.y + FXL.z*origin.z;
		float t = (na - no) / nd;
		//p=o+dt;
		XMFLOAT3 jiaodi;
		XMStoreFloat3(&jiaodi, XMLoadFloat3(&origin) + XMLoadFloat3(&direction)*t);
		return jiaodi;
	}
	float m[4][4];
	std::wstring StringToWstring(const std::string &str)
	{
		std::string message;
		/*"asset/Onepiece/" +*/
	/*	if (str.length() > 30)
		{
			message = str.substr(25, str.length());
		}*/
		message = "asset/Onepiece/Texture2D/" + str;
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
		//string→wstring
		std::wstring wsmessage = cv.from_bytes(message);
		std::wcout.imbue(std::locale(""));
		std::wcout << wsmessage << std::endl;
		return wsmessage;

	}
	std::wstring StringToWstringDX(const std::string &str)
	{
		std::string message;
		/*"asset/Onepiece/" +*/
	/*	if (str.length() > 30)
		{
			message = str.substr(25, str.length());
		}*/
		message = "asset/Onepiece/Mobatex/" + str;
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
		//string→wstring
		std::wstring wsmessage = cv.from_bytes(message);
		std::wcout.imbue(std::locale(""));
		std::wcout << wsmessage << std::endl;
		return wsmessage;

	}


	std::string WStringToString(const std::wstring &wstr)
	{
		std::string str;
		int nLen = (int)wstr.length();
		str.resize(nLen, ' ');
		int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);
		if (nResult == 0)
		{
			return "";
		}
		return str;
	}
	static XMMATRIX GetXMMATRIX(XMFLOAT4X4 Xmmfloat44)
	{
		XMMATRIX _XMMATRIX;
		_XMMATRIX = XMLoadFloat4x4(&Xmmfloat44);
		return _XMMATRIX;
	}
	static XMFLOAT4X4 ToXMFLOAT4X4(XMMATRIX _XMMATRIX)
	{
		XMFLOAT4X4 xm44;
		XMStoreFloat4x4(&xm44, _XMMATRIX);
		return xm44;
	}
	static XMMATRIX GetanimationMatrix(const aiMatrix3x3& AssimpMatrix)
	{
		XMMATRIX m;
		m = XMMatrixSet(AssimpMatrix.a1, AssimpMatrix.a2, AssimpMatrix.a3, 0.0f,
			AssimpMatrix.b1, AssimpMatrix.b2, AssimpMatrix.b3, 0.0f,
			AssimpMatrix.c1, AssimpMatrix.c2, AssimpMatrix.c3, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		return m;
	}
	float Determinant() const
	{
		return m[0][0] * m[1][1] * m[2][2] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] + m[0][0] * m[1][2] * m[2][3] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3]
			+ m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][2] * m[2][3] * m[3][0] + m[0][1] * m[1][2] * m[2][0] * m[3][3]
			- m[0][1] * m[1][3] * m[2][0] * m[3][2] + m[0][1] * m[1][3] * m[2][2] * m[3][0] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2]
			+ m[0][2] * m[1][3] * m[2][0] * m[3][1] - m[0][2] * m[1][3] * m[2][1] * m[3][0] + m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1]
			+ m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1]
			- m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][3] * m[1][2] * m[2][1] * m[3][0];
	}
	Tool& Inverse() {

		// Compute the reciprocal determinant
		float det = Determinant();
		if (det == 0.0f)
		{
			// Matrix not invertible. Setting all elements to nan is not really
			// correct in a mathematical sense but it is easy to debug for the
			// programmer.
			/*const float nan = std::numeric_limits<float>::quiet_NaN();
			*this = Matrix4f(
				nan,nan,nan,nan,
				nan,nan,nan,nan,
				nan,nan,nan,nan,
				nan,nan,nan,nan);*/
			assert(0);
			return *this;
		}

		float invdet = 1.0f / det;


		return *this;
						}
	static void covertoangle(float* radian)
	{
		float angle;
		
		 angle = *radian * 180 / PIx;
		 *radian = (int)(angle + 0.5f);
	}
	static int  LoadText(const char* Txt)
	{
		FILE *fpRead = fopen("Txt.txt", "r");
		if (fpRead == NULL) return 0;
		assert(fpRead);
		int a = 0;
		fscanf(fpRead, "%d ", &a);
		return a;
	}
	static void MoveLight(SpotlLight& light)
	{
		light.position.x = CRenderer::LightMove3_0[0];
		light.position.y = CRenderer::LightMove3_0[1];
		light.position.z = CRenderer::LightMove3_0[2];

		light.diffuse.x = CRenderer::LightMove3_1[0];
		light.diffuse.y = CRenderer::LightMove3_1[1];
		light.diffuse.z = CRenderer::LightMove3_1[2];

		light.direction.x = CRenderer::LightMove3_2[0];
		light.direction.y = CRenderer::LightMove3_2[1];
		light.direction.z = CRenderer::LightMove3_2[2];
		
		light.specular.x = CRenderer::LightMove3_3[0];
		light.specular.y = CRenderer::LightMove3_3[1];
		light.specular.z = CRenderer::LightMove3_3[2];

		light.ambient.x = CRenderer::LightMove3_4[0];
		light.ambient.y = CRenderer::LightMove3_4[1];
		light.ambient.z = CRenderer::LightMove3_4[2];

		light.constant = CRenderer::LightMove1_0[0];
		light.Linear = CRenderer::LightMove1_1[0];;
		light.quadratic = CRenderer::LightMove1_2[0];
		light.cutOff = std::cos(XMConvertToRadians(CRenderer::LightMove1_3[0]));
		light.outerCutOff = std::cos(XMConvertToRadians(CRenderer::LightMove1_4[0]));
	}
	static void MoveSun(LIGHT& light)
	{
		/*light.Direction.x = CRenderer::values[0];
		light.Direction.y = CRenderer::values[1];
		light.Direction.z = CRenderer::values[2];*/

		light.Diffuse.r= CRenderer::values[3];
		light.Diffuse.g = CRenderer::values[4];
		light.Diffuse.b = CRenderer::values[5];

		//CRenderer::values[7] = 0.158f;
		light.Ambient.r = CRenderer::values[6];
		light.Ambient.g = CRenderer::values[7];
		light.Ambient.b = CRenderer::values[8];

	/*	light.Specular.x = CRenderer::values[9];
		light.Specular.y = CRenderer::values[10];
		light.Specular.z = CRenderer::values[11];*/

	}


private:

};

