#include "stdafx.h"
#include "TextureList.h"

PAG::TextureList::TextureList()
{
}

PAG::TextureList::~TextureList()
{
    for (auto& pair : _colorTexture)
    {
        delete pair.second;
    }

    for (auto& pair : _imageTexture)
    {
        delete pair.second;
    }
}

PAG::Texture* PAG::TextureList::getTexture(const vec4& color)
{
    PAG::Texture* texture = nullptr;
    auto it = _colorTexture.find(color);

    if (it == _colorTexture.end())
    {
        texture = new PAG::Texture(color);
        _colorTexture[color] = texture;
    }
    else
        texture = it->second;

    return texture;
}

PAG::Texture* PAG::TextureList::getTexture(const std::string& path)
{
    PAG::Texture* texture = nullptr;
    auto it = _imageTexture.find(path);

    if (it == _imageTexture.end())
    {
        try
        {
            texture = new PAG::Texture(new Image(path));
            _imageTexture[path] = texture;
        }
        catch (std::runtime_error& error)
        {
            return nullptr;
        }
    }
    else
    {
        texture = it->second;
    }

    return texture;
}

void PAG::TextureList::saveTexture(const vec4& color, PAG::Texture* texture)
{
    _colorTexture[color] = texture;
}

void PAG::TextureList::saveTexture(const std::string& path, PAG::Texture* texture)
{
    _imageTexture[path] = texture;
}
