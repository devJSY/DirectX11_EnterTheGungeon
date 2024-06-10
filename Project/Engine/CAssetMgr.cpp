#include "pch.h"
#include "CAssetMgr.h"
#include "CPathMgr.h"
#include "CTaskMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"

#include "CDevice.h"
#include "CSound.h"

CAssetMgr::CAssetMgr()
{
}

CAssetMgr::~CAssetMgr()
{
}

void CAssetMgr::init()
{
    CreateDefaultMesh();
    CreateDefaultGraphicsShader();
    CreateDefaultComputeShader();
    CreateDefaultMaterial();
    CreateDefaultPhysics2DMaterial();
    CreateDefaultPhysicMaterial();

    initSound();
}

void CAssetMgr::initSound()
{
    FMOD::System_Create(&CSound::g_pFMOD);

    if (nullptr == CSound::g_pFMOD)
    {
        assert(nullptr);
    }

    // 32개 채널 생성
    CSound::g_pFMOD->init(32, FMOD_DEFAULT, nullptr);
}

void CAssetMgr::ReloadContent()
{
    LoadAssetsFromFile(CPathMgr::GetContentPath());

    // 원본 파일이 삭제된 에셋은 메모리에서 제거
    for (UINT i = 0; i < (UINT)ASSET_TYPE::END; i++)
    {
        for (const auto& pair : m_mapAsset[i])
        {
            if (pair.second->IsEngineAsset())
                continue;

            wstring strFilePath = CPathMgr::GetContentPath() + pair.first;
            if (!std::filesystem::exists(strFilePath))
            {
                LOG(Warning, "%s Source File Deleted!", ToString(strFilePath).c_str());

                GamePlayStatic::DeleteAsset((ASSET_TYPE)i, pair.second);
            }
        }
    }
}

void CAssetMgr::SaveAssetsToFile()
{
    for (UINT i = 0; i < (UINT)ASSET_TYPE::END; i++)
    {
        for (const auto& pair : m_mapAsset[i])
        {
            pair.second->Save(pair.first);
        }
    }
}

void CAssetMgr::LoadAssetsFromFile(std::filesystem::path _EntryPath)
{
    using namespace std::filesystem;

    for (auto& directoryEntry : directory_iterator(_EntryPath))
    {
        // 디렉토리 인경우 하위 디렉토리 순회
        if (directoryEntry.is_directory())
        {
            LoadAssetsFromFile(directoryEntry);
        }
        else
        {
            path FilePath = directoryEntry.path();
            path FileRelativePath = FilePath.lexically_relative(CPathMgr::GetContentPath());
            path FileExtension = FilePath.extension();

            if (FileExtension == L".mesh")
                Load<CMesh>(FileRelativePath, FileRelativePath);
            if (FileExtension == L".mdat")
                Load<CMeshData>(FileRelativePath, FileRelativePath);
            if (FileExtension == L".pref")
                Load<CPrefab>(FileRelativePath, FileRelativePath);
            if (FileExtension == L".dds" || FileExtension == L".DDS" || FileExtension == L".tga" || FileExtension == L".TGA" ||
                FileExtension == L".png" || FileExtension == L".PNG" || FileExtension == L".bmp" || FileExtension == L".BMP" ||
                FileExtension == L".jpg" || FileExtension == L".JPG" || FileExtension == L".jpeg" || FileExtension == L".JPEG")
                Load<CTexture>(FileRelativePath, FileRelativePath);
            if (FileExtension == L".mtrl")
                Load<CMaterial>(FileRelativePath, FileRelativePath);
            if (FileExtension == L".wav" || FileExtension == L".mp3" || FileExtension == L".ogg")
                Load<CSound>(FileRelativePath, FileRelativePath);
            if (FileExtension == L".physic2Dmtrl")
                Load<CPhysics2DMaterial>(FileRelativePath, FileRelativePath);
            if (FileExtension == L".physicMaterial")
                Load<CPhysicMaterial>(FileRelativePath, FileRelativePath);
        }
    }
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height, DXGI_FORMAT _pixelformat, UINT _BindFlag,
                                       D3D11_USAGE _Usage, const D3D11_DEPTH_STENCIL_VIEW_DESC* _dsvDesc,
                                       const D3D11_RENDER_TARGET_VIEW_DESC* _rtvDesc, const D3D11_SHADER_RESOURCE_VIEW_DESC* _srvDesc,
                                       const D3D11_UNORDERED_ACCESS_VIEW_DESC* _uavDesc)
{
    Ptr<CTexture> pTex = FindAsset<CTexture>(_strKey);

    assert(nullptr == pTex);

    pTex = new CTexture(true);
    if (FAILED(pTex->Create(_Width, _Height, _pixelformat, _BindFlag, _Usage, _dsvDesc, _rtvDesc, _srvDesc, _uavDesc)))
    {
        assert(nullptr);
    }

    AddAsset<CTexture>(_strKey, pTex);

    return pTex;
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _Tex2D, const D3D11_DEPTH_STENCIL_VIEW_DESC* _dsvDesc,
                                       const D3D11_RENDER_TARGET_VIEW_DESC* _rtvDesc, const D3D11_SHADER_RESOURCE_VIEW_DESC* _srvDesc,
                                       const D3D11_UNORDERED_ACCESS_VIEW_DESC* _uavDesc)
{
    Ptr<CTexture> pTex = FindAsset<CTexture>(_strKey);

    assert(nullptr == pTex);

    pTex = new CTexture(true);
    if (FAILED(pTex->Create(_Tex2D, _dsvDesc, _rtvDesc, _srvDesc, _uavDesc)))
    {
        assert(nullptr);
    }

    pTex->SetKey(_strKey);
    AddAsset<CTexture>(_strKey, pTex);

    return pTex;
}

void CAssetMgr::DeleteAsset(ASSET_TYPE _type, const wstring& _strKey)
{
    map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)_type].find(_strKey);

    assert(!(iter == m_mapAsset[(UINT)_type].end()));

    m_mapAsset[(UINT)_type].erase(iter);
}
