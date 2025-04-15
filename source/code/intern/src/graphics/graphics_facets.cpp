#include "graphics_facets.h"

#include <cassert>
#include <iostream>
#include <tinyxml2.h>

namespace Graphics
{
    // -----------------------------------------------------------------------------

    CMetaFacet::CMetaFacet(const std::string& _TexturePath)
        : m_TexturePath(_TexturePath)
    {
    }

    // -----------------------------------------------------------------------------

    const std::string& CMetaFacet::GetTexturePath() const
    {
        return m_TexturePath;
    }

    // -----------------------------------------------------------------------------

    void CMetaFacet::SetTexturePath(const std::string& _Path)
    {
        m_TexturePath = _Path;
    }

    // -----------------------------------------------------------------------------

    bool CMetaFacet::LoadFromXML(const std::string& _XmlPath)
    {
        using namespace tinyxml2;

        XMLDocument Doc;
        if (Doc.LoadFile(_XmlPath.c_str()) != XML_SUCCESS)
        {
            std::cerr << "[MetaFacet] Fehler beim Laden: " << _XmlPath << std::endl;
            return false;
        }

        XMLElement* pRoot = Doc.FirstChildElement("Graphic");
        if (!pRoot)
        {
            return false;
        }

        const char* pPath = pRoot->FirstChildElement("Texture")->GetText();
        if (!pPath)
        {
            return false;
        }

        m_TexturePath = pPath;
        return true;
    }

    // -----------------------------------------------------------------------------

    CFacet::CFacet()
        : m_Position(0.f, 0.f)
        , m_Size(0.f, 0.f)
        , m_pMetaFacet(nullptr)
    {
    }

    // -----------------------------------------------------------------------------

    void CFacet::SetPosition(float _X, float _Y)
    {
        m_Position.first = _X;
        m_Position.second = _Y;
    }

    // -----------------------------------------------------------------------------

    void CFacet::SetSize(float _Width, float _Height)
    {
        m_Size.first = _Width;
        m_Size.second = _Height;
    }

    // -----------------------------------------------------------------------------

    void CFacet::SetMetaFacet(CMetaFacet* _pMeta)
    {
        m_pMetaFacet = _pMeta;
    }

    // -----------------------------------------------------------------------------

    const std::pair<float, float>& CFacet::GetPosition() const
    {
        return m_Position;
    }

    // -----------------------------------------------------------------------------

    const std::pair<float, float>& CFacet::GetSize() const
    {
        return m_Size;
    }

    // -----------------------------------------------------------------------------

    const CMetaFacet* CFacet::GetMetaFacet() const
    {
        return m_pMetaFacet;
    }
}