#pragma once
#include "CAsset.h"

#include "CTexture.h"
#include "CGraphicsShader.h"

class CMaterial : public CAsset
{
public:
    tMtrlConst m_Const;
    Ptr<CTexture> m_arrTex[(UINT)TEX_PARAM::END];
    Ptr<CGraphicsShader> m_pShader;

public:
    void SetShader(Ptr<CGraphicsShader> _Shader) { m_pShader = _Shader; }
    Ptr<CGraphicsShader> GetShader() const { return m_pShader; }

    void SetTexParam(TEX_PARAM _Param, Ptr<CTexture> _Tex) { m_arrTex[(UINT)_Param] = _Tex; }
    Ptr<CTexture> GetTexParam(TEX_PARAM _param) const { return m_arrTex[(UINT)_param]; }

    void SetMaterialCoefficient(Vec4 _vAmb, Vec4 _vDiff, Vec4 _vSpec, Vec4 _vEmis)
    {
        m_Const.mtrl.vDiff = _vDiff;
        m_Const.mtrl.vAmb = _vAmb;
        m_Const.mtrl.vSpec = _vSpec;
        m_Const.mtrl.vEmv = _vEmis;
    }

    template <typename T>
    void SetScalarParam(SCALAR_PARAM _ParamType, const T& _Value);

    void UpdateData();

public:
    const tMtrlConst& GetMtrlConst() const { return m_Const; }

public:
    CMaterial();
    ~CMaterial();
};

template <typename T>
void CMaterial::SetScalarParam(SCALAR_PARAM _ParamType, const T& _Value)
{
    const T* pValue = &_Value;

    switch (_ParamType)
    {
    case INT_0:
    case INT_1:
    case INT_2:
    case INT_3:
        m_Const.iArr[_ParamType] = *((int*)pValue);
        break;

    case FLOAT_0:
    case FLOAT_1:
    case FLOAT_2:
    case FLOAT_3:
        m_Const.fArr[_ParamType - FLOAT_0] = *((float*)pValue);
        break;

    case VEC2_0:
    case VEC2_1:
    case VEC2_2:
    case VEC2_3:
        m_Const.v2Arr[_ParamType - VEC2_0] = *((Vec2*)pValue);

        break;
    case VEC4_0:
    case VEC4_1:
    case VEC4_2:
    case VEC4_3:
        m_Const.v4Arr[_ParamType - VEC4_0] = *((Vec4*)pValue);

        break;
    case MAT_0:
    case MAT_1:
    case MAT_2:
    case MAT_3:
        m_Const.matArr[_ParamType - MAT_0] = *((Matrix*)pValue);
        break;
    }
}