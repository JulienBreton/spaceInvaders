#include "VaisseauBonus.h"

bool CVaisseauBonus::InitialiserVaisseauBonus (sf::Image& ImageDuVaisseauBonus)
{
   ImageVaisseauBonus = ImageDuVaisseauBonus;

    SpriteVaisseauBonus.SetImage(ImageVaisseauBonus);
    SpriteVaisseauBonus.SetPosition(830, 100);
    SpriteVaisseauBonus.Resize(109, 68);

    TimerVaisseauBonus.Reset ();

    bVaisseauBonusKO = false;
    bVaisseauBonusExplose = false;

    m_TailleVaisseauBonus = GetTailleVaisseauBonus ();

    return true;
}

void CVaisseauBonus::AfficherVaisseauBonus (sf::RenderWindow& AppVaisseauBonus)
{
    if (bVaisseauBonusKO == false)
    {
        DeplacerVaisseauBonus ();
        AppVaisseauBonus.Draw(SpriteVaisseauBonus);
    }

    if (
        bVaisseauBonusKO == true
        && TimerExplosionVaisseauBonus.GetElapsedTime () < 1.f
        //&& bVaisseauBonusExplose == false
       )
    {
        IExplosionVaisseauBonus.Explosion ();
    }

    if (bVaisseauBonusKO == true
        && bVaisseauBonusExplose == true
        && TimerExplosionVaisseauBonus.GetElapsedTime () > 1.f)
    {
        TimerVaisseauBonus.Reset ();
        SpriteVaisseauBonus.SetPosition (830, 100);
        bVaisseauBonusKO = false;
        bVaisseauBonusExplose = false;
    }
}

void CVaisseauBonus::DeplacerVaisseauBonus ()
{
    sf::Vector2f PositionVaisseauBonus = SpriteVaisseauBonus.GetPosition ();

    if (TimerVaisseauBonus.GetElapsedTime () > 1.f)
    {
        SpriteVaisseauBonus.Move(- 50.f * m_fElapsedTimeVaisseauBonus, 0.f);
    }

    if (PositionVaisseauBonus.x < -100.f)
    {
        SpriteVaisseauBonus.SetPosition (830, 100);
        TimerVaisseauBonus.Reset ();
    }
}

sf::Vector2f CVaisseauBonus::GetPositionVaisseauBonus ()
{
    return SpriteVaisseauBonus.GetPosition ();
}

sf::Vector2f CVaisseauBonus::GetTailleVaisseauBonus ()
{
    return SpriteVaisseauBonus.GetSize ();
}

sf::Vector2f CVaisseauBonus::GetCentreVaisseauBonus ()
{
    return SpriteVaisseauBonus.GetCenter ();
}
