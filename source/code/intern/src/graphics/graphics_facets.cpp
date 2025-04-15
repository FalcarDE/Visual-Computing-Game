#include "graphics_facets.h"
#include <cassert>
#include <iostream>
#include <tinyxml2.h>

namespace Graphics
{
    // ==================== CMetaFacet ====================

    CMetaFacet::CMetaFacet(const std::string& _TexturePath)
        : m_TexturePath(_TexturePath)
    {
    }

    const std::string& CMetaFacet::GetTexturePath() const
    {
        return m_TexturePath;
    }

    void CMetaFacet::SetTexturePath(const std::string& _Path)
    {
        m_TexturePath = _Path;
    }

    // ==================== CFacet ====================

    CFacet::CFacet()
        : m_Position(0.f, 0.f), m_Size(0.f, 0.f), m_MetaFacet(nullptr)
    {
    }

    void CFacet::SetPosition(float x, float y)
    {
        m_Position.first = x;
        m_Position.second = y;
    }

    void CFacet::SetSize(float width, float height)
    {
        m_Size.first = width;
        m_Size.second = height;
    }

    void CFacet::SetMetaFacet(CMetaFacet* pMeta)
    {
        m_MetaFacet = pMeta;
    }

    const std::pair<float, float>& CFacet::GetPosition() const
    {
        return m_Position;
    }

    const std::pair<float, float>& CFacet::GetSize() const
    {
        return m_Size;
    }

    const CMetaFacet* CFacet::GetMetaFacet() const
    {
        return m_MetaFacet;
    }

    bool CMetaFacet::LoadFromXML(const std::string& xmlPath)
    {
        using namespace tinyxml2;

        XMLDocument doc;
        if (doc.LoadFile(xmlPath.c_str()) != XML_SUCCESS)
        {
            std::cerr << "[MetaFacet] Fehler beim Laden: " << xmlPath << std::endl;
            return false;
        }

        XMLElement* root = doc.FirstChildElement("Graphic");
        if (!root) return false;

        const char* path = root->FirstChildElement("Texture")->GetText();
        if (!path) return false;

        m_TexturePath = path;
        return true;
    }
}
