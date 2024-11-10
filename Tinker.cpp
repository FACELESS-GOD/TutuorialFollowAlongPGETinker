#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"



// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        // Name your application
        sAppName = "Bare PGE";
    }

    float Time  = 0.0f;

    float OuterRadius = 200.0f;
        
    float InnerRadius = 75.0f;

    float ratioNegative = InnerRadius / OuterRadius ; 
    float ratioPositive = OuterRadius / InnerRadius ;

    float ratioPrime = 0.0f;

    float PenRadius = 65.0f;

    float OriginX = 256.0f ;
    float OriginY = 256.0f ;

    olc::vf2d CurrPoint ; 

    olc::vf2d OriginPosition { 256.0f , 256.0f };

    bool IsFirst = true ; 

    void Reset()
    {
        Time = 0.0f;
        Clear(olc::WHITE);        
        IsFirst = true ; 
    }
    
public:
    bool OnUserCreate() override
    {
        return true;
    }
    
    bool OnUserUpdate(float GoneTime) override
    {
        if(GetKey(olc:: Key :: Q).bHeld)
        {
            ratioPrime = ratioNegative;
        }

        if(GetKey(olc:: Key :: W).bHeld)
        {
            ratioPrime = ratioPositive;
        }

        if(GetKey(olc:: Key :: A).bHeld)
        {
            Time += GoneTime * 2.0f ;
        }

        if(GetKey(olc:: Key :: S).bHeld)
        {
            Reset();
        }        

        olc::vf2d  MovingCirclePosition {
            (OuterRadius-InnerRadius) * cos(Time),
            (OuterRadius-InnerRadius) * sin(Time)
        };

        olc::vf2d PenCircleOffsetPosition {
                (PenRadius) * cos(-Time * ratioPrime),
                (PenRadius) * sin(-Time * ratioPrime),
        };

        olc::vf2d newPoint ; 

        olc::vf2d PenPosition  = OriginPosition + MovingCirclePosition + PenCircleOffsetPosition;

        newPoint.x = (OuterRadius+10) * cos(Time) + OriginX ;
        newPoint.y = (OuterRadius+10) * sin(Time) + OriginY ;

        if(IsFirst == true)
        { 
            Reset();            
            CurrPoint = newPoint ; 
            IsFirst = false;
        }

        DrawLine( CurrPoint , PenPosition, olc::BLUE); 
        
        CurrPoint = PenPosition ;        
        
        return true;
    }
};

int main()
{
    Example demo;
    if (demo.Construct(512, 512, 1, 1))        
        demo.Start();
    return 0;
}