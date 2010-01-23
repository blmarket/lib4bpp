//vertex shader for grass..
//sinusoidal vertex motion for waving grass
//pos + sumOverI(wavedirI * texcoordy * sin( xdirI * (xpos+time)) + ydirI * (ypos+time)))
// v0   - Vertex Position
// v7   - Vertex Texture Data u,v 
// c0  - commonConst ( 0.0, 0.5, 1.0, 2.0);
// c1  - appConst( time, 0.0, 0.0, 0.0);
// c4  - Composite World-View-Projection Matrix
// c8  - sin9 ( -1/3!, 1/5!, -1/7!, 1/9! )
// c10 - frcFixup ( 1.07, 0.0, 0.0, 0.0)
// c11 - waveDistortx ( 3.0, 0.4, 0.0, 0.3)
// c12 - waveDistorty ( 3.0, 0.4, 0.0, 0.3)
// c13 - waveDistortz ( -1.0, -0.133, -0.333, -0.10)
// c14 - waveDirx ( -0.006, -0.012, 0.024, 0.048)
// c15 - waveDiry ( -0.003, -0.006, -0.012, -0.048)
// c16 - waveSpeed ( 0.3, 0.6, 0.7, 1.4)
// c17 - piVector (4.0, pi/2, pi, pi*2)
// c18 - lightingWaveScale ( 0.35, 0.10, 0.10, 0.03);
// c19 - lightingScaleBias ( 0.6, 0.7, 0.2, 0.0);

vs.1.1

mul r0, c14, v0.x     // use vertex pos x as inputs to sinusoidal warp 
mad r0, c15, v0.y, r0 // use vertex pos y as inputs to sinusoidal warp 

mov r1, c1.x          // get current time
mad r0, r1, c16, r0   // add scaled time to move bumps according to speed
frc r0.xy, r0         // take frac of all 4 components
frc r1.xy, r0.zwzw    //
mov r0.zw, r1.xyxy    //
   
mul r0, r0, c10.x     // multiply by fixup factor (due to inaccuracy of taylor series)
sub r0, r0, c0.y      // subtract 0.5
mul r1, r0, c17.w     // *=2pi coords range from(-pi to pi)
   
mul r2, r1, r1        // (wave vec)^2
mul r3, r2, r1        // (wave vec)^3 
mul r5, r3, r2        // (wave vec)^5
mul r7, r5, r2        // (wave vec)^7 
mul r9, r7, r2        // (wave vec)^9
   
mad r0, r3, c8.x, r1  //(wave vec) - ((wave vec)^3)/3! 
mad r0, r5, c8.y, r0  //  + ((wave vec)^5)/5! 
mad r0, r7, c8.z, r0  //  - ((wave vec)^7)/7! 
mad r0, r9, c8.w, r0  //  - ((wave vec)^9)/9! 
   
dp4 r3.x, r0, c11
dp4 r3.y, r0, c12
dp4 r3.zw, r0, c13

sub r4, c0.z, v7.y
mul r4, r4, r4       
mul r3, r3, r4        // attenuate sinusoidal warping by (1-tex0.y)^2  

mov r2.w, v0
add r2.xyz, r3, v0	  // add sinusoidal warping to grass position

m4x4 oPos, r2, c4
dp4  r1.x, r0, c18		   	//scale and add sin waves together
mad  oD0, c19.xzxz, -r1.x, c19.y	//scale and bias color values (green is scaled more // than red and blue)
mov  oT0, v7			
