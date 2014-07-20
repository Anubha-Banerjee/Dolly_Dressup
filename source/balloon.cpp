#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 
#include <iostream>
using namespace std;
#include<stdlib.h>
#include <time.h>
#include <d3dx9.h>
#include <fstream>


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB;// Buffer to hold vertices
LPDIRECT3DTEXTURE9     g_cloths[100]  ; // Our texture - contains the mundu
LPDIRECT3DTEXTURE9     g_girl  ; // Our texture - contains the mundu
LPDIRECT3DTEXTURE9     g_girlsmall  ; // Our texture - contains the mundu
LPDIRECT3DTEXTURE9     g_girlbald  ; // Our texture - contains the mundu
LPDIRECT3DTEXTURE9     g_hand  ; // Our texture - contains the hand
LPDIRECT3DTEXTURE9      g_iTexture   = NULL; // Our texture - contains the mundu
LPDIRECT3DTEXTURE9     g_handClutch  ; // Our texture - contains the clutch
LPDIRECT3DVERTEXBUFFER9 foodVB       = NULL; //buffer 
//arrOfClothes[j][0]=100,ClothTop_y=400,ClothWidth=82,ClothHeight=168; 
int  hand_x=600,hand_y=200,handWidth=35,handHeight=41;
int mousePos_x = 0;
int mousePos_y = 0;
int carryingCloth=0;
int moving=0,pressing=0;
int currentCloth=0,nxtlif=0,i=0;
int screen=0;
char ins='a';
int canSelectNewCloth=1;

int arrOfClothes[][4]={
	                   
					   10,200,171,158,//sweater
	                   100,400,82,168,
					   10,600,117,79,//boots
					   400,200,143,169,
                       500,400,107,111,
                       300,400,117,135, 
                       100,200,160,269,  
					   400,200,160,269,
                       200,600,107,31, 
					   300,500,96,120,//veil
					   10,10,85,47,//hat

				
                       300,500,143,200,//slacks
					   200,100,172,208,//black skirt
					   400,100,236,167,//purpl skirt
                       100,100,164,112,//pink skirt
					   300,100,177,184,//pink top
					   900,500,227,450,//dressBlack
					   300,100,239,198,//sweater
					   400,100,254,214,//pink sweater
					   600,200,271,219,//jacket
					   300,300,196,192,//braids
					   400,300,142,179,//st. hair
					   500,300,167,239,//open hair
                       800,500,178,45,//shu
					   200,-20,115,149,//full face
                       10,50,27,11,//nose
					   10,70,38,16,//big smile
					   10,116,34,16,//smile
					   10,200,32,17,//laugh
					   10,250,38,17,//grin
					   10,300,28,13,//sad
					   10,350,30,18,//anger
					   10,400,36,16,//normal
					   40,10,89,31,
					   40,100,89,27,
					   40,200,84,26,
					   40,300,90,33,
					   40,400,87,31,
					   40,500,85,29,
					   40,600,85,29,
					   200,600,192,50,//sandal
					   80,10,116,35,//earrings
					   100,10,58,32,//neckclasp
					   200,10,104,55,//necklace
					   300,10,266,32,//bangles
					   80,10,116,35,//bangle earrings

                       









                      
                       400,600,47,86,//sock
					   400,550,43,34,//balck shoes
					   460,550,46,27,//red shu 
					   400,200,76,177,//pajama
					   100,600,70,136,//pantpurple
					   200,200,97,120,//skirt
					   500,200,66,74,//blue skirt
					   100,100,90,108,//hairblonde
                       100,200,135,236,//gownshred                     
                       200,100,63,61, //bun flower    
					   350,200,73,105,//pink top
					   200,400,93,201,//black dress
					   100,550,51,28,//white shoes
					   300,550,86,96,//redShirt
					   200,550,68,94,//black strap
					 
					   250,100,88,152,//braid
					   300,100,88,102,//pony
					
					   400,200,98,265,//sari
					   300,200,87,148,//kurti
					   300,300,92,159,//fock
					   400,400,209,301,//gown
					   300,500,108,123,//sweater
					   100,10,81,123,//chunri
					   200,10,69,163,//haed wrap
					   

					



					


                      };
int NoOfCloths1=11;
int NoOfCloths2=35;
int NoOfCloths3=24;
int NoOfCloths=0;


wchar_t clothes[][50]   =
                {
                   
					L"sweater1.bmp",
					L"pant.bmp",
					L"boots.bmp",
					L"lehenga.bmp",
					L"skirt.bmp",
					L"top.bmp",
                    L"dresswhite.bmp",
					L"pinkDress.bmp",
					L"shoesMaroon.bmp",
                    L"veil.bmp", 
					L"hat.bmp",
				
                   
					L"slacks.bmp",
					L"blackSkirt.bmp",
					L"purpleSkirt.bmp",
					L"pinkSkirtPrinted.bmp",
					L"pinkTop.bmp",
                    L"dressBlack.bmp",  
					L"sweater.bmp",
					L"pinkSweater.bmp",
					L"jacket.bmp",
					L"2braids.bmp",
					L"hairBlack.bmp",
					L"hairOpen.bmp",
					L"pinkShoes.bmp",
                    L"fullFace.bmp",
					L"nose.bmp",
					L"bigSmile.bmp",
					L"smile.bmp",
					L"laugh.bmp",
					L"grin.bmp",
					L"sad.bmp",
					L"angry.bmp",
					L"normal.bmp",
					L"bigEyes.bmp",
					L"smallEyes.bmp",
					L"angryEyes.bmp",
					L"halfEyes.bmp",
					L"closedEyes.bmp",
					L"surprisedEyes.bmp",
					L"upEyes.bmp",
					L"sandals.bmp",
					L"earrings.bmp",
					L"neckclasp.bmp",
					L"necklace.bmp",
					L"bangles.bmp",
					L"bangles.bmp",
					


					
					L"socks.bmp",
					L"blackHeels.bmp",
					L"redShoes.bmp",
					L"pajama.bmp",
                  	L"purplePant.bmp",
                    L"skirtPrintedBlue.bmp",
                    L"blueSkirt.bmp",
  					L"hairBlonde.bmp",
                   	L"dressShred.bmp",
					L"bunFlower.bmp",
					L"topsleevless.bmp",
					L"blackDress.bmp",
					L"shoesWhite.bmp",
					L"redShirt.bmp",
                    L"blackStrap.bmp",
					L"braid.bmp",  
                    L"hairchoti.bmp",  
					L"purpleSari.bmp",
					L"kurta.bmp",
					L"frock.bmp",
					L"gown.bmp",
					L"sweatertrans.bmp",
					L"chunri.bmp",
					L"headWrap.bmp",
					

					
                 };

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    float x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color

	FLOAT       tu, tv;   // The texture coordinates
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)




//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	/*
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	*/
	
    d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = 1024;
	d3dpp.BackBufferHeight = 768;
	
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

     // Create the D3DDevice
     if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
     {
        return E_FAIL;
     }

     // Device state would normally be set here
    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

 for(int k=0;k<(NoOfCloths1+NoOfCloths2+NoOfCloths3);k++)
  {
    D3DXCreateTextureFromFileEx( g_pd3dDevice, (LPCWSTR)	clothes[k],     
	0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0,&g_cloths[k]);
  }  
    
    D3DXCreateTextureFromFileEx( g_pd3dDevice, L"girl.bmp",     
	0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_girlsmall);  
  
    D3DXCreateTextureFromFileEx( g_pd3dDevice, L"girl2.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_girl); 
	  D3DXCreateTextureFromFileEx( g_pd3dDevice, L"girl3.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_girlbald);  
	 D3DXCreateTextureFromFileEx( g_pd3dDevice, L"hand.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_hand); 
    	 D3DXCreateTextureFromFileEx( g_pd3dDevice, L"handClutch.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_handClutch); 
		 D3DXCreateTextureFromFileEx( g_pd3dDevice, L"startPage.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_iTexture);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chunk of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------




HRESULT InitVB()
{   

    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
	 g_pd3dDevice->CreateVertexBuffer( 200*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL );
	    g_pd3dDevice->CreateVertexBuffer( 300*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT,&foodVB , NULL );
    


    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{   
	if( g_pVB != NULL )        
        g_pVB->Release();

	  

    

    if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )       
        g_pD3D->Release();
}


void carryCloth()
{


arrOfClothes[currentCloth][0]=mousePos_x-(arrOfClothes[currentCloth][2]/2) ;
arrOfClothes[currentCloth][1]= mousePos_y-(arrOfClothes[currentCloth][3]/2); 


}

void drawclothes()
{
int j=0;
if(screen==1)
{
 NoOfCloths=NoOfCloths1;
 j=0;
}
if(screen==2)
{
 NoOfCloths=NoOfCloths1+NoOfCloths2;
 j=NoOfCloths1;
}
if(screen==3)
{
 NoOfCloths=NoOfCloths1+NoOfCloths2+NoOfCloths3;
 j=NoOfCloths1+NoOfCloths2;
}
 CUSTOMVERTEX food[10];
  for(;j<NoOfCloths;j++)
     {
	
        food[0].x =  arrOfClothes[j][0]  ;
		food[0].y = arrOfClothes[j][1]+ arrOfClothes[j][3];
		food[0].z = 1;
		food[0].rhw = 1;
		food[0].color = D3DCOLOR_XRGB(255,255,255);
        food[0].tu=0;
        food[0].tv=1;

		food[1].x = arrOfClothes[j][0]  ;
		food[1].y = arrOfClothes[j][1];
		food[1].z = 1;
		food[1].rhw = 1;
		food[1].color = D3DCOLOR_XRGB(255,255,255);
        food[1].tu=0;
        food[1].tv=0;



        food[2].x = arrOfClothes[j][0] + arrOfClothes[j][2] ;
		food[2].y = arrOfClothes[j][1]+ arrOfClothes[j][3];
		food[2].z = 1;
		food[2].rhw = 1;
		food[2].color = D3DCOLOR_XRGB(255,255,255);
        food[2].tu=1;
        food[2].tv=1;


        food[3].x = arrOfClothes[j][0] + arrOfClothes[j][2] ;
		food[3].y = arrOfClothes[j][1];
		food[3].z = 1;
		food[3].rhw = 1;
		food[3].color = D3DCOLOR_XRGB(255,255,255);
        food[3].tu=1;
        food[3].tv=0;


        void *pVertices;
		
		g_pd3dDevice->SetStreamSource( 0, foodVB, 0, sizeof(CUSTOMVERTEX) );
	    g_pd3dDevice->SetTexture(0, g_cloths[j]);
        foodVB->Lock( 0, sizeof(food), (void**)&pVertices, 0 );
        memcpy( pVertices, food, sizeof(food) );
        foodVB->Unlock();
        g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0,2);
  }
   
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------

void Render() 
{
    
    CUSTOMVERTEX vertices[] =
	{
		 //big girl
		{ 600,0,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 600,681,  0, 1.0f, 0xFFFFFFFF, 0,1},
        { 910,681,  0, 1.0f, 0xFFFFFFFF, 1,1},

        { 600,0,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 910,0, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 910,681, 0, 1.0f, 0xFFFFFFFF, 1,1},

       
       
        //hand
		{ hand_x,hand_y,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { hand_x,hand_y+handHeight,  0, 1.0f, 0xFFFFFFFF, 0,1},
        { hand_x+handWidth,hand_y+handHeight,  0, 1.0f, 0xFFFFFFFF, 1,1},

        { hand_x,hand_y, 0,  1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { hand_x+handWidth,hand_y, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { hand_x+handWidth,hand_y+handHeight,0,1.0f, 0xFFFFFFFF, 1,1},  

		  //smallgirl
		{ 600,200,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 600,616,  0, 1.0f, 0xFFFFFFFF, 0,1},
        { 794,616,  0, 1.0f, 0xFFFFFFFF, 1,1},

        { 600,200,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 794,200, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 794,616, 0, 1.0f, 0xFFFFFFFF, 1,1},

		//instruction screen
		 { 0, 0,  0, 1.0f,0xFFFFFFFF , 0,0}, // x, y, z, rhw, color,tex
        {  0,768, 0, 1.0f,0xFFFFFFFF , 0,1},
        { 1024,768, 0, 1.0f,0xFFFFFFFF , 1,1},

        { 0, 0,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 1024, 0, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 1024, 768, 0, 1.0f, 0xFFFFFFFF, 1,1},
		       
	};



   
		
	 if(moving==1&&pressing==1)
	   {
         carryCloth();
	   }
 
     

	

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device (GPU) memory.
    VOID* pVertices;
	

	g_pVB->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );
 
    memcpy( pVertices, vertices, sizeof(vertices) );

    g_pVB->Unlock();

 





	// Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(138,217,255), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Draw the triangles in the vertex buffer. This is broken into a few
        // steps. We are passing the vertices down a "stream", so first we need
        // to specify the source of that stream, which is our vertex buffer. Then
        // we need to let D3D know what vertex shader to use. Full, custom vertex
        // shaders are an advanced topic, but in most cases the vertex shader is
        // just the FVF, so that D3D knows what type of vertices we are dealing
        // with. Finally, we call DrawPrimitive() which does the actual rendering
        // of our geometry (in this case, not just one triangle).
		hand_x=mousePos_x-20;
		hand_y=mousePos_y-20;
	
		
     
	  
	    
    	
	        	
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
		g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );

		  if(ins!='n')
	     {
          g_pd3dDevice->SetTexture(0, g_iTexture);
          g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,18,2 );
         } 

		else
		{
		if(screen==1)
		{
	    //draw girl
		g_pd3dDevice->SetTexture(0, g_girlsmall);
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,12,2);
		} 

		if(screen==2)
		{
	    //draw girl
		g_pd3dDevice->SetTexture(0, g_girl);
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,0,2);
		} 
		
		if(screen==3)
		{
	    //draw girl
		g_pd3dDevice->SetTexture(0, g_girlbald);
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,12,2);
		} 
		if(screen==4)
		{
        exit(0);
		} 


        drawclothes();  

        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
		g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
		//draw hand
		if(pressing==1)
		{
          
		g_pd3dDevice->SetTexture(0, g_handClutch);
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 6,2);
   
		}
		else
		{
        
		g_pd3dDevice->SetTexture(0, g_hand);
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 6,2);

		}
				
		
		
	 }
		// End the scene
		  g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{   
	moving=0;
	
    switch( msg )
    {
        case WM_DESTROY:
			
            Cleanup();
            PostQuitMessage( 0 );
            return 0;

		
		

		case WM_KEYDOWN:
			
			ins='n';

			if(wParam == VK_ESCAPE)
			{
				Cleanup();
				PostQuitMessage( 0 );
				return 0;
			}

			if(wParam == VK_RIGHT)
			{
				screen=screen+1;
			}

		case WM_MOUSEMOVE:
			mousePos_x = lParam & 0xFFFF;
			mousePos_y = lParam >> 16;
            moving=1;
         for(i=0;i<NoOfCloths;i++)
		   {
 			if((mousePos_x>arrOfClothes[i][0]&&mousePos_x<arrOfClothes[i][0]+arrOfClothes[i][2]&&mousePos_y>arrOfClothes[i][1]&&mousePos_y<arrOfClothes[i][1]+arrOfClothes[i][3])&&canSelectNewCloth==1)
			  {
				
				currentCloth=i;
                
			  }
		   }
			break;

      
	  case WM_LBUTTONUP:
		    pressing=0;
			canSelectNewCloth=1;
			break;
			
      
	  case WM_LBUTTONDOWN:
			   pressing=1;
			   canSelectNewCloth=0;
               break; 
		


			return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{   

	ShowCursor(0);
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      L"D3D Tutorial", NULL };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 02: Vertices",
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              NULL, NULL, wc.hInstance, NULL );
    



     // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the vertex buffer
        if( SUCCEEDED( InitVB() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
				else
				{   
					
 					Render();
				}
            }
        }
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}
