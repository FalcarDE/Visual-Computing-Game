#pragma once

#include <string>
#include <utility> 

namespace Graphics
{
    class CMetaFacet
    {
    public:
        CMetaFacet(const std::string& _TexturePath);

        const std::string& GetTexturePath() const;
        void SetTexturePath(const std::string& _Path);
        bool LoadFromXML(const std::string& xmlPath);

    private:
        std::string m_TexturePath;
    };

    class CFacet
    {
    public:
        CFacet();

        void SetPosition(float x, float y);
        void SetSize(float width, float height);
        void SetMetaFacet(CMetaFacet* pMeta);

        const std::pair<float, float>& GetPosition() const;
        const std::pair<float, float>& GetSize() const;
        const CMetaFacet* GetMetaFacet() const;

    private:
        std::pair<float, float> m_Position;
        std::pair<float, float> m_Size;
        CMetaFacet* m_MetaFacet;
    };
}
