#include "TileIsoHexa.hpp"

#include <string>
#include <math.h>


const float PI = 3.14159265;

constexpr float n = 50.0;
constexpr float sin_75 = sin(75*PI/180)*n;
constexpr float sin_15 = sin(15*PI/180)*n;
constexpr float sin_45 = sin(45*PI/180)*n;
constexpr float r_hauteur = sin_15+sin_45+sin_75;

constexpr float decalage_x = sin_45-sin_15;
constexpr float decalage_y = sin_75+sin_45;



namespace map
{
    sf::Font TileIsoHexa::font;

    TileIsoHexa::TileIsoHexa(const int& X, const int& Y) : sprite(0)
    {
        shape.setPointCount(6);
        shape.setPoint(0,sf::Vector2f(0,(sin_15+sin_75)/2));
        shape.setPoint(1,sf::Vector2f(sin_15,sin_15/2));
        shape.setPoint(2,sf::Vector2f(sin_15+sin_75,0));
        shape.setPoint(3,sf::Vector2f(sin_15+sin_75+sin_45,sin_45/2));
        shape.setPoint(4,sf::Vector2f(sin_75+sin_45,(sin_75+sin_45)/2));
        shape.setPoint(5,sf::Vector2f(sin_45,(sin_15+sin_75+sin_45)/2));

        shape.setOrigin(r_hauteur/2,r_hauteur/4);

        //shape.setFillColor(sf::Color::Red);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);


        /*txt.setFont(font);
        txt.setCharacterSize(20);
        txt.setColor(sf::Color(255,255,255,100));*/


        setPosition(X,Y);
    };


    void TileIsoHexa::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape,states);
        //target.draw(txt,states);
        if(sprite)
            target.draw(*sprite,states);
    };

    sf::Vector2i TileIsoHexa::toLocal(const int& X,const int& Y)
    {
         const int a = X + r_hauteur/2;
         const int b = Y + r_hauteur/4;
         const float x =(2*b*decalage_x - a*decalage_y)/(decalage_x*decalage_x - decalage_y*decalage_y);
         const float y= (2*b-x*decalage_x)/decalage_y;

         return sf::Vector2i((x<0)?x-1:x,(y<0)?y-1:y);

    };

    sf::Vector2i TileIsoHexa::toLocal(const sf::Vector2i& pos)
    {
        return TileIsoHexa::toLocal(pos.x,pos.y);
    };

    sf::Vector2f TileIsoHexa::toGlobal(const int& X,const int& Y)
    {
        return sf::Vector2f(Y*decalage_x+X*decalage_y,Y*decalage_y/2+X*decalage_x/2);
    };

    sf::Vector2f TileIsoHexa::toGlobal(const sf::Vector2i& pos)
    {
        return toGlobal(pos.x,pos.y);
    }


    void TileIsoHexa::setPosition(const int& X,const int& Y)
    {
        sf::Vector2f pos(toGlobal(X,Y));
        shape.setPosition(pos);
        if(sprite)
            sprite->setPosition(pos);

         /*std::string text= std::to_string(X) + " " + std::to_string(Y);
         txt.setString(text);
         sf::FloatRect rec = txt.getLocalBounds();
         txt.setOrigin(rec.width/2,rec.height/2);

         txt.setPosition(shape.getPosition());*/

    };

    void TileIsoHexa::setTexture(const sf::Texture *texture,bool resetRect)
    {
            shape.setTexture(texture,resetRect);
    };

    void TileIsoHexa::setSprite(sf::Sprite*& spr)
    {
        if(sprite)
            delete sprite;
        sprite = spr;
        sprite.setPosition(shape.getPosition());
    };

    void TileIsoHexa::setSprite(const sf::Texture& tex)
    {
        if(sprite)
            sprite->setTexture(tex);
        else
        {
            sprite = new sf::Sprite(tex);
            sprite.setPosition(shape.getPosition());
        }
    };

};
