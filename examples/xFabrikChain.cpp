/*
 * =====================================================================================
 *
 *       Filename:  xFabrikChain.cpp
 *
 *    Description:  "FABRIK" Iterative Solver
                    (see paper Aristodou and Lasenby "Inverse Kinematic Solutions using Conformal Geometric Algebra")
 *
 *        Version:  1.0
 *        Created:  07/20/2015 19:56:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Pablo Colapinto (), gmail->wolftype
 *   Organization:  wolftype
 *
 * =====================================================================================
 */


#include <vsr/vsr_app.h>
#include <vsr/form/vsr_chain.h>
#include <vsr/draw/vsr_chain_draw.h>

using namespace vsr;
using namespace vsr::cga;


struct MyApp : App {

  //Some Variables
  bool bReset = false;
  float amt = 0;


  //Chain of 10 links
  Chain chain = Chain(10);

  //whether to relcaculate joint positions
  bool bFK;
  /*-----------------------------------------------------------------------------
   *  Setup Variables
   *-----------------------------------------------------------------------------*/
  void setup(){
    ///Add Variables to GUI
    gui(amt,"amt",-100,100)(bReset,"bReset");

  }


  /*-----------------------------------------------------------------------------
   *  Draw Routines
   *-----------------------------------------------------------------------------*/
  void onDraw(){
    //intersection of ray cast by mouse into space and the xy plane
    calcMouse3D();
    Point point = Construct::meet (mMouseRay, Dlp(0,0,1,0));

    //Draw point on xy plane as small red circle.  This is our "target"
    auto marker = Construct::sphere (point,.2);
    draw(marker,1,0,0);

    //pass in beginning, ending index, adjust error threshold
    chain.fabrik(point,chain.num()-1,0,amt);
    //recalculate forward kinematics
    chain.fk();

   // draw(chain);

    for (int i = 0;i<chain.num(); ++i){
      draw( chain[i]);
      draw( chain.nextLine(i),1,0,0);
      draw( chain.nextSphere(i),0,1,1,.3);
    }

  }

  void onKeyDown(const gfx::Keyboard &k){
    if (k.code=='q') bFK = !bFK;
  }

};


int main(){

  MyApp app;
  app.start();

  return 0;

}
