xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 428;
 -207.06834;18.93073;-11.08010;,
 -210.39138;8.73293;-11.08010;,
 -246.89949;18.93073;-11.08010;,
 -224.89976;8.73293;-11.08010;,
 -250.22217;8.73293;-11.08010;,
 -235.70220;8.73293;-11.08010;,
 -262.27898;-22.33310;-11.08010;,
 -258.95552;-12.13580;-11.08010;,
 -218.48880;-22.33310;-11.08010;,
 -242.38824;-12.13580;-11.08010;,
 -215.16573;-12.13580;-11.08010;,
 -231.65242;-12.13580;-11.08010;,
 -166.89087;2.78133;-11.08010;,
 -171.25491;-10.66140;-11.08010;,
 -195.17903;-9.10235;-11.08010;,
 -199.04071;-22.33310;-11.08010;,
 -186.07504;18.93073;-11.08010;,
 -196.86869;18.93073;-11.08010;,
 -210.26807;-22.33310;-11.08010;,
 -170.79423;-22.33310;-11.08010;,
 -147.27265;1.14842;-11.08011;,
 -156.64209;-22.33310;-11.08011;,
 -142.13217;-7.84703;-11.08011;,
 -115.30875;18.93073;-11.08011;,
 -135.36350;-1.09180;-11.08011;,
 -129.46104;18.93073;-11.08011;,
 -140.50333;7.90365;-11.08011;,
 -157.42748;18.93073;-11.08010;,
 -146.79911;18.93073;-11.08011;,
 -126.70294;-16.25801;-11.08011;,
 -137.33123;-16.25801;-11.08011;,
 -67.48971;3.43584;-11.08011;,
 -75.85216;-22.33310;-11.08011;,
 -78.28302;3.43584;-11.08011;,
 -83.32018;-12.13580;-11.08011;,
 -119.65138;-22.33310;-11.08011;,
 -116.33235;-12.13580;-11.08011;,
 -83.55852;18.93073;-11.08011;,
 -86.88116;8.73293;-11.08011;,
 -106.25288;18.93073;-11.08011;,
 -109.57235;8.73293;-11.08011;,
 -43.43612;18.93073;-11.08012;,
 -48.47327;3.37402;-11.08011;,
 -54.23134;18.93073;-11.08011;,
 -67.63012;-22.33310;-11.08011;,
 -24.05294;3.37402;-11.08012;,
 -27.37195;-6.82372;-11.08012;,
 -51.79966;-6.82372;-11.08011;,
 -56.83681;-22.33310;-11.08011;,
 63.32886;18.39183;-11.08012;,
 58.94117;3.72502;-11.08012;,
 14.45887;3.60750;-11.08012;,
 45.06678;-0.24539;-11.08012;,
 10.07112;-9.90555;-11.08012;,
 31.19512;-3.95137;-11.08012;,
 37.88890;-22.32867;-11.08012;,
 25.49083;-22.33265;-11.08012;,
 68.06516;8.73293;-11.08012;,
 71.38823;18.93073;-11.08012;,
 101.07468;8.73293;-11.08013;,
 115.18899;18.93073;-11.08013;,
 101.78977;-22.33310;-11.08013;,
 90.99573;-22.33310;-11.08013;,
 162.17804;3.37402;-11.08013;,
 153.81684;-22.33310;-11.08013;,
 151.38489;3.37402;-11.08013;,
 146.34765;-12.13580;-11.08013;,
 110.01764;-22.33310;-11.08013;,
 113.34060;-12.13580;-11.08013;,
 141.06848;3.37402;-11.08013;,
 137.74953;-6.82372;-11.08013;,
 118.37807;3.37402;-11.08013;,
 115.05907;-6.82372;-11.08013;,
 146.10995;18.93073;-11.08013;,
 142.78689;8.73293;-11.08013;,
 123.41963;18.93073;-11.08013;,
 120.09660;8.73293;-11.08013;,
 160.58858;22.86673;-11.08013;,
 155.97743;8.73293;-11.08013;,
 156.38383;22.86673;-11.08013;,
 151.77710;8.73293;-11.08013;,
 170.52230;22.86673;-11.08013;,
 165.91552;8.73293;-11.08013;,
 166.32208;22.86673;-11.08013;,
 161.71529;8.73293;-11.08013;,
 205.60247;3.37402;-11.08014;,
 202.28352;-6.82372;-11.08014;,
 170.38233;3.37402;-11.08013;,
 167.06333;-6.82372;-11.08013;,
 210.12449;-6.82372;-11.08014;,
 218.48665;18.93073;-11.08014;,
 220.92256;-6.82372;-11.08014;,
 225.96397;8.73293;-11.08014;,
 262.28172;18.93073;-11.08014;,
 248.15196;8.73293;-11.08014;,
 248.88289;-22.33310;-11.08014;,
 246.44544;3.37402;-11.08014;,
 226.61910;-6.82372;-11.08014;,
 229.93824;3.37402;-11.08014;,
 243.11248;-6.82372;-11.08014;,
 241.40669;-12.13580;-11.08014;,
 221.57771;-22.33310;-11.08014;,
 224.90078;-12.13580;-11.08014;,
 -246.89949;18.93073;11.08014;,
 -210.39138;8.73293;11.08014;,
 -207.06834;18.93073;11.08014;,
 -224.89976;8.73293;11.08014;,
 -235.70220;8.73293;11.08014;,
 -250.22217;8.73293;11.08014;,
 -218.48880;-22.33310;11.08014;,
 -258.95552;-12.13580;11.08014;,
 -262.27898;-22.33310;11.08014;,
 -242.38824;-12.13580;11.08014;,
 -231.65242;-12.13580;11.08014;,
 -215.16573;-12.13580;11.08014;,
 -195.17903;-9.10235;11.08013;,
 -171.25491;-10.66140;11.08013;,
 -166.89087;2.78133;11.08013;,
 -199.04071;-22.33310;11.08013;,
 -196.86869;18.93073;11.08013;,
 -186.07504;18.93073;11.08013;,
 -210.26807;-22.33310;11.08014;,
 -156.64209;-22.33310;11.08013;,
 -147.27265;1.14842;11.08013;,
 -170.79423;-22.33310;11.08013;,
 -142.13217;-7.84703;11.08013;,
 -129.46104;18.93073;11.08013;,
 -135.36350;-1.09180;11.08013;,
 -115.30875;18.93073;11.08013;,
 -140.50333;7.90365;11.08013;,
 -146.79911;18.93073;11.08013;,
 -157.42748;18.93073;11.08013;,
 -137.33123;-16.25801;11.08013;,
 -126.70294;-16.25801;11.08013;,
 -78.28302;3.43584;11.08012;,
 -75.85216;-22.33310;11.08012;,
 -67.48971;3.43584;11.08012;,
 -83.32018;-12.13580;11.08012;,
 -119.65138;-22.33310;11.08013;,
 -116.33235;-12.13580;11.08013;,
 -106.25288;18.93073;11.08013;,
 -86.88116;8.73293;11.08012;,
 -83.55852;18.93073;11.08012;,
 -109.57235;8.73293;11.08013;,
 -54.23134;18.93073;11.08012;,
 -48.47327;3.37402;11.08012;,
 -43.43612;18.93073;11.08012;,
 -67.63012;-22.33310;11.08012;,
 -27.37195;-6.82372;11.08012;,
 -24.05294;3.37402;11.08012;,
 -51.79966;-6.82372;11.08012;,
 -56.83681;-22.33310;11.08012;,
 14.45887;3.60750;11.08012;,
 58.94117;3.72502;11.08011;,
 63.32886;18.39183;11.08011;,
 45.06678;-0.24539;11.08011;,
 31.19512;-3.95137;11.08012;,
 10.07112;-9.90555;11.08012;,
 37.88890;-22.32867;11.08011;,
 25.49083;-22.33265;11.08012;,
 101.07468;8.73293;11.08011;,
 71.38823;18.93073;11.08011;,
 68.06516;8.73293;11.08011;,
 115.18899;18.93073;11.08011;,
 101.78977;-22.33310;11.08011;,
 90.99573;-22.33310;11.08011;,
 151.38489;3.37402;11.08010;,
 153.81684;-22.33310;11.08010;,
 162.17804;3.37402;11.08010;,
 146.34765;-12.13580;11.08011;,
 110.01764;-22.33310;11.08011;,
 113.34060;-12.13580;11.08011;,
 118.37807;3.37402;11.08011;,
 137.74953;-6.82372;11.08011;,
 141.06848;3.37402;11.08011;,
 115.05907;-6.82372;11.08011;,
 123.41963;18.93073;11.08011;,
 142.78689;8.73293;11.08011;,
 146.10995;18.93073;11.08011;,
 120.09660;8.73293;11.08011;,
 156.38383;22.86673;11.08010;,
 155.97743;8.73293;11.08010;,
 160.58858;22.86673;11.08010;,
 151.77710;8.73293;11.08010;,
 166.32208;22.86673;11.08010;,
 165.91552;8.73293;11.08010;,
 170.52230;22.86673;11.08010;,
 161.71529;8.73293;11.08010;,
 170.38233;3.37402;11.08010;,
 202.28352;-6.82372;11.08010;,
 205.60247;3.37402;11.08010;,
 167.06333;-6.82372;11.08010;,
 220.92256;-6.82372;11.08010;,
 218.48665;18.93073;11.08010;,
 210.12449;-6.82372;11.08010;,
 225.96397;8.73293;11.08010;,
 262.28172;18.93073;11.08009;,
 248.15196;8.73293;11.08010;,
 248.88289;-22.33310;11.08010;,
 246.44544;3.37402;11.08010;,
 243.11248;-6.82372;11.08010;,
 229.93824;3.37402;11.08010;,
 226.61910;-6.82372;11.08010;,
 241.40669;-12.13580;11.08010;,
 221.57771;-22.33310;11.08010;,
 224.90078;-12.13580;11.08010;,
 -212.89124;-10.48472;-13.05486;,
 -229.38286;-10.48472;-13.05486;,
 -217.29031;-23.98418;-13.05486;,
 -264.55362;-23.98418;-13.05485;,
 -252.49666;7.08184;-13.05485;,
 -237.96494;7.08184;-13.05485;,
 -248.09807;20.58182;-13.05485;,
 -204.79388;20.58182;-13.05486;,
 -209.19290;7.08184;-13.05486;,
 -223.69866;7.08184;-13.05486;,
 -243.59309;-10.48472;-13.05485;,
 -260.15391;-10.48472;-13.05485;,
 -164.20768;5.69933;-13.05486;,
 -192.49533;-6.18406;-13.05486;,
 -169.91804;-11.89072;-13.05486;,
 -198.70800;-23.98418;-13.05486;,
 -212.54012;-23.98418;-13.05486;,
 -198.06851;20.58182;-13.05486;,
 -183.80285;20.58182;-13.05486;,
 -111.31820;20.58182;-13.05486;,
 -130.14420;20.58182;-13.05486;,
 -133.30402;-1.36872;-13.05486;,
 -140.14097;10.59888;-13.05486;,
 -174.78509;-23.98418;-13.05486;,
 -155.95901;-23.98418;-13.05486;,
 -149.33214;1.42541;-13.05486;,
 -142.49492;-10.54226;-13.05486;,
 -123.85880;-17.90909;-13.05486;,
 -138.28992;-17.90909;-13.05486;,
 -160.27169;20.58182;-13.05486;,
 -145.84060;20.58182;-13.05486;,
 -121.92511;-23.98418;-13.05486;,
 -74.65208;-23.98418;-13.05487;,
 -117.53130;-10.48472;-13.05486;,
 -84.52135;-10.48472;-13.05487;,
 -65.21809;5.08692;-13.05487;,
 -79.48419;5.08692;-13.05487;,
 -111.84608;7.08184;-13.05486;,
 -85.68264;7.08184;-13.05487;,
 -107.45177;20.58182;-13.05486;,
 -81.28411;20.58182;-13.05487;,
 -21.77926;5.02510;-13.05487;,
 -46.20321;5.02510;-13.05487;,
 -26.17299;-8.47481;-13.05487;,
 -50.59990;-8.47481;-13.05487;,
 -69.90218;-23.98418;-13.05487;,
 -55.63705;-23.98418;-13.05487;,
 -55.43111;20.58182;-13.05487;,
 -41.16597;20.58182;-13.05487;,
 7.44910;-12.63439;-13.05488;,
 28.57199;-6.67245;-13.05488;,
 13.13574;4.87877;-13.05488;,
 65.95088;21.12073;-13.05488;,
 60.26423;2.45360;-13.05488;,
 46.38962;-1.51696;-13.05488;,
 39.08845;-23.97930;-13.05488;,
 23.21788;-23.98462;-13.05488;,
 88.72426;-23.98418;-13.05488;,
 102.98952;-23.98418;-13.05488;,
 98.80321;7.08184;-13.05488;,
 117.46101;20.58182;-13.05488;,
 70.18972;20.58182;-13.05488;,
 65.79067;7.08184;-13.05488;,
 107.74304;-23.98418;-13.05488;,
 155.01602;-23.98418;-13.05489;,
 112.14210;-10.48472;-13.05488;,
 145.14787;-10.48472;-13.05489;,
 164.45127;5.02510;-13.05489;,
 150.18509;5.02510;-13.05489;,
 112.78530;-8.47481;-13.05488;,
 138.94846;-8.47481;-13.05489;,
 117.17903;5.02510;-13.05488;,
 143.34220;5.02510;-13.05489;,
 117.82207;7.08184;-13.05488;,
 143.98540;7.08184;-13.05489;,
 122.22114;20.58182;-13.05489;,
 148.38451;20.58182;-13.05489;,
 149.50231;7.08184;-13.05489;,
 157.17558;7.08184;-13.05489;,
 155.18548;24.51781;-13.05489;,
 162.86386;24.51781;-13.05489;,
 159.44055;7.08184;-13.05489;,
 167.11399;7.08184;-13.05489;,
 165.12367;24.51781;-13.05489;,
 172.79702;24.51781;-13.05489;,
 164.78957;-8.47481;-13.05489;,
 203.48250;-8.47481;-13.05489;,
 169.18336;5.02510;-13.05489;,
 207.87625;5.02510;-13.05489;,
 219.30313;-23.98418;-13.05490;,
 250.08269;-23.98418;-13.05490;,
 223.70227;-10.48472;-13.05490;,
 240.20271;-10.48472;-13.05490;,
 264.55362;20.58182;-13.05490;,
 240.84825;-8.47481;-13.05490;,
 224.34551;-8.47481;-13.05490;,
 228.73916;5.02510;-13.05490;,
 245.23843;5.02510;-13.05490;,
 245.89339;7.08184;-13.05490;,
 217.28682;20.58182;-13.05489;,
 227.16453;7.08184;-13.05490;,
 207.85252;-8.47481;-13.05489;,
 222.12317;-8.47481;-13.05490;,
 -229.38286;-10.48472;13.05489;,
 -212.89124;-10.48472;13.05489;,
 -217.29031;-23.98418;13.05489;,
 -264.55362;-23.98418;13.05490;,
 -237.96494;7.08184;13.05490;,
 -252.49666;7.08184;13.05490;,
 -248.09807;20.58182;13.05490;,
 -204.79388;20.58182;13.05489;,
 -209.19290;7.08184;13.05489;,
 -223.69866;7.08184;13.05489;,
 -243.59309;-10.48472;13.05490;,
 -260.15391;-10.48472;13.05490;,
 -192.49533;-6.18406;13.05489;,
 -164.20768;5.69933;13.05489;,
 -169.91804;-11.89072;13.05489;,
 -198.70800;-23.98418;13.05489;,
 -212.54012;-23.98418;13.05489;,
 -198.06851;20.58182;13.05489;,
 -183.80285;20.58182;13.05489;,
 -130.14420;20.58182;13.05488;,
 -111.31820;20.58182;13.05488;,
 -133.30402;-1.36872;13.05488;,
 -140.14097;10.59888;13.05489;,
 -155.95901;-23.98418;13.05489;,
 -174.78509;-23.98418;13.05489;,
 -149.33214;1.42541;13.05489;,
 -142.49492;-10.54226;13.05489;,
 -123.85880;-17.90909;13.05488;,
 -138.28992;-17.90909;13.05489;,
 -160.27169;20.58182;13.05489;,
 -145.84060;20.58182;13.05489;,
 -74.65208;-23.98418;13.05488;,
 -121.92511;-23.98418;13.05488;,
 -117.53130;-10.48472;13.05488;,
 -84.52135;-10.48472;13.05488;,
 -65.21809;5.08692;13.05488;,
 -79.48419;5.08692;13.05488;,
 -85.68264;7.08184;13.05488;,
 -111.84608;7.08184;13.05488;,
 -107.45177;20.58182;13.05488;,
 -81.28411;20.58182;13.05488;,
 -46.20321;5.02510;13.05488;,
 -21.77926;5.02510;13.05488;,
 -26.17299;-8.47481;13.05488;,
 -50.59990;-8.47481;13.05488;,
 -55.63705;-23.98418;13.05488;,
 -69.90218;-23.98418;13.05488;,
 -55.43111;20.58182;13.05488;,
 -41.16597;20.58182;13.05488;,
 28.57199;-6.67245;13.05487;,
 7.44910;-12.63439;13.05487;,
 13.13574;4.87877;13.05487;,
 65.95088;21.12073;13.05487;,
 60.26423;2.45360;13.05487;,
 46.38962;-1.51696;13.05487;,
 39.08845;-23.97930;13.05487;,
 23.21788;-23.98462;13.05487;,
 102.98952;-23.98418;13.05486;,
 88.72426;-23.98418;13.05486;,
 98.80321;7.08184;13.05486;,
 117.46101;20.58182;13.05486;,
 70.18972;20.58182;13.05487;,
 65.79067;7.08184;13.05487;,
 155.01602;-23.98418;13.05486;,
 107.74304;-23.98418;13.05486;,
 112.14210;-10.48472;13.05486;,
 145.14787;-10.48472;13.05486;,
 164.45127;5.02510;13.05486;,
 150.18509;5.02510;13.05486;,
 138.94846;-8.47481;13.05486;,
 112.78530;-8.47481;13.05486;,
 117.17903;5.02510;13.05486;,
 143.34220;5.02510;13.05486;,
 143.98540;7.08184;13.05486;,
 117.82207;7.08184;13.05486;,
 122.22114;20.58182;13.05486;,
 148.38451;20.58182;13.05486;,
 157.17558;7.08184;13.05486;,
 149.50231;7.08184;13.05486;,
 155.18548;24.51781;13.05486;,
 162.86386;24.51781;13.05486;,
 167.11399;7.08184;13.05486;,
 159.44055;7.08184;13.05486;,
 165.12367;24.51781;13.05486;,
 172.79702;24.51781;13.05486;,
 203.48250;-8.47481;13.05486;,
 164.78957;-8.47481;13.05486;,
 169.18336;5.02510;13.05486;,
 207.87625;5.02510;13.05486;,
 250.08269;-23.98418;13.05485;,
 219.30313;-23.98418;13.05485;,
 223.70227;-10.48472;13.05485;,
 240.20271;-10.48472;13.05485;,
 264.55362;20.58182;13.05485;,
 240.84825;-8.47481;13.05485;,
 224.34551;-8.47481;13.05485;,
 228.73916;5.02510;13.05485;,
 245.23843;5.02510;13.05485;,
 245.89339;7.08184;13.05485;,
 217.28682;20.58182;13.05486;,
 227.16453;7.08184;13.05485;,
 207.85252;-8.47481;13.05486;,
 222.12317;-8.47481;13.05485;,
 1.85013;5.59681;-11.08012;,
 -2.53761;-7.47845;-11.08012;,
 -10.55363;2.86443;-11.08012;,
 -14.94137;-9.90555;-11.08012;,
 -10.55363;2.86443;11.08012;,
 -2.53761;-7.47845;11.08012;,
 1.85013;5.59681;11.08012;,
 -14.94137;-9.90555;11.08012;,
 4.22516;7.79264;-13.05724;,
 -11.69173;4.28631;-13.05724;,
 -1.40528;-9.22622;-13.05724;,
 -17.32216;-12.10035;-13.05724;,
 -11.69172;4.28631;13.05724;,
 4.22516;7.79264;13.05724;,
 -1.40527;-9.22622;13.05724;,
 -17.32216;-12.10035;13.05724;;
 
 514;
 3;0,1,2;,
 3;1,3,2;,
 3;4,2,5;,
 3;2,3,5;,
 3;6,7,8;,
 3;7,9,8;,
 3;10,8,11;,
 3;8,9,11;,
 3;9,5,11;,
 3;5,3,11;,
 3;12,13,14;,
 3;13,15,14;,
 3;16,14,17;,
 3;17,14,18;,
 3;18,14,15;,
 3;19,20,21;,
 3;21,20,22;,
 3;23,24,25;,
 3;25,24,26;,
 3;27,28,20;,
 3;28,26,20;,
 3;29,30,24;,
 3;30,22,24;,
 3;22,20,24;,
 3;20,26,24;,
 3;31,32,33;,
 3;33,32,34;,
 3;32,35,34;,
 3;34,35,36;,
 3;37,38,39;,
 3;38,40,39;,
 3;41,42,43;,
 3;43,42,44;,
 3;45,46,42;,
 3;46,47,42;,
 3;42,47,44;,
 3;44,47,48;,
 3;49,50,51;,
 3;50,52,51;,
 3;53,51,54;,
 3;51,52,54;,
 3;52,55,54;,
 3;54,55,56;,
 3;57,58,59;,
 3;58,60,59;,
 3;60,61,59;,
 3;59,61,62;,
 3;63,64,65;,
 3;65,64,66;,
 3;64,67,66;,
 3;66,67,68;,
 3;69,70,71;,
 3;70,72,71;,
 3;73,74,75;,
 3;74,76,75;,
 3;77,78,79;,
 3;78,80,79;,
 3;81,82,83;,
 3;82,84,83;,
 3;85,86,87;,
 3;86,88,87;,
 3;89,90,91;,
 3;91,90,92;,
 3;90,93,92;,
 3;92,93,94;,
 3;93,95,94;,
 3;94,95,96;,
 3;97,98,99;,
 3;98,96,99;,
 3;96,95,99;,
 3;99,95,100;,
 3;95,101,100;,
 3;100,101,102;,
 3;103,104,105;,
 3;103,106,104;,
 3;107,103,108;,
 3;107,106,103;,
 3;109,110,111;,
 3;109,112,110;,
 3;113,109,114;,
 3;113,112,109;,
 3;113,107,112;,
 3;113,106,107;,
 3;115,116,117;,
 3;115,118,116;,
 3;119,115,120;,
 3;121,115,119;,
 3;118,115,121;,
 3;122,123,124;,
 3;125,123,122;,
 3;126,127,128;,
 3;129,127,126;,
 3;123,130,131;,
 3;123,129,130;,
 3;127,132,133;,
 3;127,125,132;,
 3;127,123,125;,
 3;127,129,123;,
 3;134,135,136;,
 3;137,135,134;,
 3;137,138,135;,
 3;139,138,137;,
 3;140,141,142;,
 3;140,143,141;,
 3;144,145,146;,
 3;147,145,144;,
 3;145,148,149;,
 3;145,150,148;,
 3;147,150,145;,
 3;151,150,147;,
 3;152,153,154;,
 3;152,155,153;,
 3;156,152,157;,
 3;156,155,152;,
 3;156,158,155;,
 3;159,158,156;,
 3;160,161,162;,
 3;160,163,161;,
 3;160,164,163;,
 3;165,164,160;,
 3;166,167,168;,
 3;169,167,166;,
 3;169,170,167;,
 3;171,170,169;,
 3;172,173,174;,
 3;172,175,173;,
 3;176,177,178;,
 3;176,179,177;,
 3;180,181,182;,
 3;180,183,181;,
 3;184,185,186;,
 3;184,187,185;,
 3;188,189,190;,
 3;188,191,189;,
 3;192,193,194;,
 3;195,193,192;,
 3;195,196,193;,
 3;197,196,195;,
 3;197,198,196;,
 3;199,198,197;,
 3;200,201,202;,
 3;200,199,201;,
 3;200,198,199;,
 3;203,198,200;,
 3;203,204,198;,
 3;205,204,203;,
 4;0,105,104,1;,
 4;2,103,105,0;,
 4;1,104,106,3;,
 4;4,108,103,2;,
 4;5,107,108,4;,
 4;6,111,110,7;,
 4;8,109,111,6;,
 4;7,110,112,9;,
 4;10,114,109,8;,
 4;11,113,114,10;,
 4;9,112,107,5;,
 4;3,106,113,11;,
 4;12,117,116,13;,
 4;14,115,117,12;,
 4;13,116,118,15;,
 4;16,120,115,14;,
 4;17,119,120,16;,
 4;18,121,119,17;,
 4;15,118,121,18;,
 4;19,124,123,20;,
 4;21,122,124,19;,
 4;22,125,122,21;,
 4;23,128,127,24;,
 4;25,126,128,23;,
 4;26,129,126,25;,
 4;27,131,130,28;,
 4;20,123,131,27;,
 4;28,130,129,26;,
 4;29,133,132,30;,
 4;24,127,133,29;,
 4;30,132,125,22;,
 4;31,136,135,32;,
 4;33,134,136,31;,
 4;34,137,134,33;,
 4;32,135,138,35;,
 4;35,138,139,36;,
 4;36,139,137,34;,
 4;37,142,141,38;,
 4;39,140,142,37;,
 4;38,141,143,40;,
 4;40,143,140,39;,
 4;41,146,145,42;,
 4;43,144,146,41;,
 4;44,147,144,43;,
 4;45,149,148,46;,
 4;42,145,149,45;,
 4;46,148,150,47;,
 4;47,150,151,48;,
 4;48,151,147,44;,
 4;49,154,153,50;,
 4;51,152,154,49;,
 4;50,153,155,52;,
 4;53,157,152,51;,
 4;54,156,157,53;,
 4;52,155,158,55;,
 4;55,158,159,56;,
 4;56,159,156,54;,
 4;57,162,161,58;,
 4;59,160,162,57;,
 4;58,161,163,60;,
 4;60,163,164,61;,
 4;61,164,165,62;,
 4;62,165,160,59;,
 4;63,168,167,64;,
 4;65,166,168,63;,
 4;66,169,166,65;,
 4;64,167,170,67;,
 4;67,170,171,68;,
 4;68,171,169,66;,
 4;69,174,173,70;,
 4;71,172,174,69;,
 4;70,173,175,72;,
 4;72,175,172,71;,
 4;73,178,177,74;,
 4;75,176,178,73;,
 4;74,177,179,76;,
 4;76,179,176,75;,
 4;77,182,181,78;,
 4;79,180,182,77;,
 4;78,181,183,80;,
 4;80,183,180,79;,
 4;81,186,185,82;,
 4;83,184,186,81;,
 4;82,185,187,84;,
 4;84,187,184,83;,
 4;85,190,189,86;,
 4;87,188,190,85;,
 4;86,189,191,88;,
 4;88,191,188,87;,
 4;89,194,193,90;,
 4;91,192,194,89;,
 4;92,195,192,91;,
 4;90,193,196,93;,
 4;94,197,195,92;,
 4;93,196,198,95;,
 4;96,199,197,94;,
 4;97,202,201,98;,
 4;99,200,202,97;,
 4;98,201,199,96;,
 4;100,203,200,99;,
 4;95,198,204,101;,
 4;101,204,205,102;,
 4;102,205,203,100;,
 3;206,207,208;,
 3;208,207,209;,
 3;210,211,212;,
 3;212,211,213;,
 3;214,213,215;,
 3;213,211,215;,
 3;215,211,207;,
 3;211,216,207;,
 3;207,216,209;,
 3;209,216,217;,
 3;218,219,220;,
 3;220,219,221;,
 3;222,221,223;,
 3;221,219,223;,
 3;219,224,223;,
 3;225,226,227;,
 3;226,228,227;,
 3;229,230,231;,
 3;230,232,231;,
 3;233,227,234;,
 3;234,227,232;,
 3;235,231,236;,
 3;236,231,228;,
 3;228,231,227;,
 3;227,231,232;,
 3;237,238,239;,
 3;239,238,240;,
 3;238,241,240;,
 3;240,241,242;,
 3;243,244,245;,
 3;244,246,245;,
 3;247,248,249;,
 3;249,248,250;,
 3;251,252,253;,
 3;252,250,253;,
 3;250,248,253;,
 3;248,254,253;,
 3;255,256,257;,
 3;258,257,259;,
 3;259,257,260;,
 3;257,256,260;,
 3;260,256,261;,
 3;261,256,262;,
 3;263,264,265;,
 3;264,266,265;,
 3;266,267,265;,
 3;265,267,268;,
 3;269,270,271;,
 3;271,270,272;,
 3;270,273,272;,
 3;272,273,274;,
 3;275,276,277;,
 3;276,278,277;,
 3;279,280,281;,
 3;280,282,281;,
 3;283,284,285;,
 3;284,286,285;,
 3;287,288,289;,
 3;288,290,289;,
 3;291,292,293;,
 3;292,294,293;,
 3;295,296,297;,
 3;297,296,298;,
 3;296,299,298;,
 3;298,299,300;,
 3;301,300,302;,
 3;302,300,303;,
 3;300,299,303;,
 3;303,299,304;,
 3;299,305,304;,
 3;304,305,306;,
 3;305,307,306;,
 3;306,307,308;,
 3;309,310,311;,
 3;309,311,312;,
 3;313,314,315;,
 3;313,315,316;,
 3;316,317,318;,
 3;313,316,318;,
 3;313,318,309;,
 3;319,313,309;,
 3;319,309,312;,
 3;319,312,320;,
 3;321,322,323;,
 3;321,323,324;,
 3;324,325,326;,
 3;321,324,326;,
 3;327,321,326;,
 3;328,329,330;,
 3;331,328,330;,
 3;332,333,334;,
 3;335,332,334;,
 3;330,336,337;,
 3;330,337,335;,
 3;334,338,339;,
 3;334,339,331;,
 3;334,331,330;,
 3;334,330,335;,
 3;340,341,342;,
 3;340,342,343;,
 3;344,340,343;,
 3;344,343,345;,
 3;346,347,348;,
 3;349,346,348;,
 3;350,351,352;,
 3;350,352,353;,
 3;354,355,356;,
 3;353,354,356;,
 3;350,353,356;,
 3;357,350,356;,
 3;358,359,360;,
 3;360,361,362;,
 3;360,362,363;,
 3;358,360,363;,
 3;358,363,364;,
 3;358,364,365;,
 3;366,367,368;,
 3;369,366,368;,
 3;370,369,368;,
 3;370,368,371;,
 3;372,373,374;,
 3;372,374,375;,
 3;376,372,375;,
 3;376,375,377;,
 3;378,379,380;,
 3;381,378,380;,
 3;382,383,384;,
 3;385,382,384;,
 3;386,387,388;,
 3;389,386,388;,
 3;390,391,392;,
 3;393,390,392;,
 3;394,395,396;,
 3;397,394,396;,
 3;398,399,400;,
 3;398,400,401;,
 3;402,398,401;,
 3;402,401,403;,
 3;403,404,405;,
 3;403,405,406;,
 3;402,403,406;,
 3;402,406,407;,
 3;408,402,407;,
 3;408,407,409;,
 3;410,408,409;,
 3;410,409,411;,
 4;206,208,311,310;,
 4;207,206,310,309;,
 4;208,209,312,311;,
 4;210,212,315,314;,
 4;211,210,314,313;,
 4;212,213,316,315;,
 4;214,215,318,317;,
 4;213,214,317,316;,
 4;215,207,309,318;,
 4;216,211,313,319;,
 4;209,217,320,312;,
 4;217,216,319,320;,
 4;218,220,323,322;,
 4;219,218,322,321;,
 4;220,221,324,323;,
 4;222,223,326,325;,
 4;221,222,325,324;,
 4;223,224,327,326;,
 4;224,219,321,327;,
 4;225,227,330,329;,
 4;226,225,329,328;,
 4;228,226,328,331;,
 4;229,231,334,333;,
 4;230,229,333,332;,
 4;232,230,332,335;,
 4;233,234,337,336;,
 4;227,233,336,330;,
 4;234,232,335,337;,
 4;235,236,339,338;,
 4;231,235,338,334;,
 4;236,228,331,339;,
 4;237,239,342,341;,
 4;238,237,341,340;,
 4;239,240,343,342;,
 4;241,238,340,344;,
 4;240,242,345,343;,
 4;242,241,344,345;,
 4;243,245,348,347;,
 4;244,243,347,346;,
 4;245,246,349,348;,
 4;246,244,346,349;,
 4;247,249,352,351;,
 4;248,247,351,350;,
 4;249,250,353,352;,
 4;251,253,356,355;,
 4;252,251,355,354;,
 4;250,252,354,353;,
 4;253,254,357,356;,
 4;254,248,350,357;,
 4;255,257,360,359;,
 4;256,255,359,358;,
 4;258,259,362,361;,
 4;257,258,361,360;,
 4;259,260,363,362;,
 4;260,261,364,363;,
 4;261,262,365,364;,
 4;262,256,358,365;,
 4;263,265,368,367;,
 4;264,263,367,366;,
 4;266,264,366,369;,
 4;267,266,369,370;,
 4;265,268,371,368;,
 4;268,267,370,371;,
 4;269,271,374,373;,
 4;270,269,373,372;,
 4;271,272,375,374;,
 4;273,270,372,376;,
 4;272,274,377,375;,
 4;274,273,376,377;,
 4;275,277,380,379;,
 4;276,275,379,378;,
 4;277,278,381,380;,
 4;278,276,378,381;,
 4;279,281,384,383;,
 4;280,279,383,382;,
 4;281,282,385,384;,
 4;282,280,382,385;,
 4;283,285,388,387;,
 4;284,283,387,386;,
 4;285,286,389,388;,
 4;286,284,386,389;,
 4;287,289,392,391;,
 4;288,287,391,390;,
 4;289,290,393,392;,
 4;290,288,390,393;,
 4;291,293,396,395;,
 4;292,291,395,394;,
 4;293,294,397,396;,
 4;294,292,394,397;,
 4;295,297,400,399;,
 4;296,295,399,398;,
 4;297,298,401,400;,
 4;299,296,398,402;,
 4;298,300,403,401;,
 4;301,302,405,404;,
 4;300,301,404,403;,
 4;302,303,406,405;,
 4;303,304,407,406;,
 4;305,299,402,408;,
 4;304,306,409,407;,
 4;307,305,408,410;,
 4;306,308,411,409;,
 4;308,307,410,411;,
 3;412,413,414;,
 3;415,414,413;,
 3;416,417,418;,
 3;417,416,419;,
 4;412,418,417,413;,
 4;414,416,418,412;,
 4;415,419,416,414;,
 4;413,417,419,415;,
 3;420,421,422;,
 3;423,422,421;,
 3;424,425,426;,
 3;426,427,424;,
 4;420,422,426,425;,
 4;421,420,425,424;,
 4;423,421,424,427;,
 4;422,423,427,426;;
 
 MeshMaterialList {
  2;
  514;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.000000;0.000000;;
  }
 }
}