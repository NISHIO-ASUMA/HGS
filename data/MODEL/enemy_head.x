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
 238;
 -4.31500;9.59786;-3.03668;,
 4.31500;9.59786;-3.03668;,
 4.31500;0.03786;-3.03668;,
 -4.31500;0.03786;-3.03668;,
 4.31500;9.59786;-3.03668;,
 4.31500;9.59786;2.97332;,
 4.31500;0.03786;2.97332;,
 4.31500;0.03786;-3.03668;,
 4.31500;9.59786;2.97332;,
 -4.31500;9.59786;2.97332;,
 -4.31500;0.03786;2.97332;,
 4.31500;0.03786;2.97332;,
 -4.31500;9.59786;2.97332;,
 -4.31500;9.59786;-3.03668;,
 -4.31500;0.03786;-3.03668;,
 -4.31500;0.03786;2.97332;,
 4.31500;9.59786;-3.03668;,
 -4.31500;9.59786;-3.03668;,
 -4.31500;0.03786;-3.03668;,
 4.31500;0.03786;-3.03668;,
 -2.03443;7.50058;-2.41005;,
 -1.76383;7.42445;-2.68065;,
 -2.03443;7.42445;-2.79273;,
 -2.03443;7.50058;-2.41005;,
 -1.65175;7.42445;-2.41005;,
 -2.03443;7.50058;-2.41005;,
 -1.76383;7.42445;-2.13945;,
 -2.03443;7.50058;-2.41005;,
 -2.03443;7.42445;-2.02736;,
 -2.03443;7.50058;-2.41005;,
 -2.30503;7.42445;-2.13945;,
 -2.03443;7.50058;-2.41005;,
 -2.41711;7.42445;-2.41005;,
 -2.03443;7.50058;-2.41005;,
 -2.30503;7.42445;-2.68065;,
 -2.03443;7.50058;-2.41005;,
 -2.03443;7.42445;-2.79273;,
 -1.53443;7.20768;-2.91005;,
 -2.03443;7.20768;-3.11716;,
 -1.32732;7.20768;-2.41005;,
 -1.53443;7.20768;-1.91005;,
 -2.03443;7.20768;-1.70294;,
 -2.53443;7.20768;-1.91005;,
 -2.74154;7.20768;-2.41005;,
 -2.53443;7.20768;-2.91005;,
 -2.03443;7.20768;-3.11716;,
 -1.38115;6.88326;-3.06333;,
 -2.03443;6.88326;-3.33393;,
 -1.11055;6.88326;-2.41005;,
 -1.38115;6.88326;-1.75677;,
 -2.03443;6.88326;-1.48617;,
 -2.68771;6.88326;-1.75677;,
 -2.95831;6.88326;-2.41005;,
 -2.68771;6.88326;-3.06333;,
 -2.03443;6.88326;-3.33393;,
 -1.32732;6.50058;-3.11716;,
 -2.03443;6.50058;-3.41005;,
 -1.03443;6.50058;-2.41005;,
 -1.32732;6.50058;-1.70294;,
 -2.03443;6.50058;-1.41005;,
 -2.74154;6.50058;-1.70294;,
 -3.03443;6.50058;-2.41005;,
 -2.74154;6.50058;-3.11716;,
 -2.03443;6.50058;-3.41005;,
 -1.38115;6.11789;-3.06333;,
 -2.03443;6.11789;-3.33393;,
 -1.11055;6.11789;-2.41005;,
 -1.38115;6.11789;-1.75677;,
 -2.03443;6.11789;-1.48617;,
 -2.68771;6.11789;-1.75677;,
 -2.95831;6.11789;-2.41005;,
 -2.68771;6.11789;-3.06333;,
 -2.03443;6.11789;-3.33393;,
 -1.53443;5.79347;-2.91005;,
 -2.03443;5.79347;-3.11716;,
 -1.32732;5.79347;-2.41005;,
 -1.53443;5.79347;-1.91005;,
 -2.03443;5.79347;-1.70294;,
 -2.53443;5.79347;-1.91005;,
 -2.74154;5.79347;-2.41005;,
 -2.53443;5.79347;-2.91005;,
 -2.03443;5.79347;-3.11716;,
 -1.76383;5.57670;-2.68065;,
 -2.03443;5.57670;-2.79273;,
 -1.65175;5.57670;-2.41005;,
 -1.76383;5.57670;-2.13945;,
 -2.03443;5.57670;-2.02736;,
 -2.30503;5.57670;-2.13945;,
 -2.41711;5.57670;-2.41005;,
 -2.30503;5.57670;-2.68065;,
 -2.03443;5.57670;-2.79273;,
 -2.03443;5.50058;-2.41005;,
 -2.03443;5.50058;-2.41005;,
 -2.03443;5.50058;-2.41005;,
 -2.03443;5.50058;-2.41005;,
 -2.03443;5.50058;-2.41005;,
 -2.03443;5.50058;-2.41005;,
 -2.03443;5.50058;-2.41005;,
 -2.03443;5.50058;-2.41005;,
 2.00120;7.50058;-2.41005;,
 2.27179;7.42445;-2.68065;,
 2.00120;7.42445;-2.79273;,
 2.00120;7.50058;-2.41005;,
 2.38388;7.42445;-2.41005;,
 2.00120;7.50058;-2.41005;,
 2.27179;7.42445;-2.13945;,
 2.00120;7.50058;-2.41005;,
 2.00120;7.42445;-2.02736;,
 2.00120;7.50058;-2.41005;,
 1.73060;7.42445;-2.13945;,
 2.00120;7.50058;-2.41005;,
 1.61851;7.42445;-2.41005;,
 2.00120;7.50058;-2.41005;,
 1.73060;7.42445;-2.68065;,
 2.00120;7.50058;-2.41005;,
 2.00120;7.42445;-2.79273;,
 2.50120;7.20768;-2.91005;,
 2.00120;7.20768;-3.11716;,
 2.70830;7.20768;-2.41005;,
 2.50120;7.20768;-1.91005;,
 2.00120;7.20768;-1.70294;,
 1.50120;7.20768;-1.91005;,
 1.29409;7.20768;-2.41005;,
 1.50120;7.20768;-2.91005;,
 2.00120;7.20768;-3.11716;,
 2.65448;6.88326;-3.06333;,
 2.00120;6.88326;-3.33393;,
 2.92507;6.88326;-2.41005;,
 2.65448;6.88326;-1.75677;,
 2.00120;6.88326;-1.48617;,
 1.34791;6.88326;-1.75677;,
 1.07732;6.88326;-2.41005;,
 1.34791;6.88326;-3.06333;,
 2.00120;6.88326;-3.33393;,
 2.70830;6.50058;-3.11716;,
 2.00120;6.50058;-3.41005;,
 3.00120;6.50058;-2.41005;,
 2.70830;6.50058;-1.70294;,
 2.00120;6.50058;-1.41005;,
 1.29409;6.50058;-1.70294;,
 1.00120;6.50058;-2.41005;,
 1.29409;6.50058;-3.11716;,
 2.00120;6.50058;-3.41005;,
 2.65448;6.11789;-3.06333;,
 2.00120;6.11789;-3.33393;,
 2.92507;6.11789;-2.41005;,
 2.65448;6.11789;-1.75677;,
 2.00120;6.11789;-1.48617;,
 1.34791;6.11789;-1.75677;,
 1.07732;6.11789;-2.41005;,
 1.34791;6.11789;-3.06333;,
 2.00120;6.11789;-3.33393;,
 2.50120;5.79347;-2.91005;,
 2.00120;5.79347;-3.11716;,
 2.70830;5.79347;-2.41005;,
 2.50120;5.79347;-1.91005;,
 2.00120;5.79347;-1.70294;,
 1.50120;5.79347;-1.91005;,
 1.29409;5.79347;-2.41005;,
 1.50120;5.79347;-2.91005;,
 2.00120;5.79347;-3.11716;,
 2.27179;5.57670;-2.68065;,
 2.00120;5.57670;-2.79273;,
 2.38388;5.57670;-2.41005;,
 2.27179;5.57670;-2.13945;,
 2.00120;5.57670;-2.02736;,
 1.73060;5.57670;-2.13945;,
 1.61851;5.57670;-2.41005;,
 1.73060;5.57670;-2.68065;,
 2.00120;5.57670;-2.79273;,
 2.00120;5.50058;-2.41005;,
 2.00120;5.50058;-2.41005;,
 2.00120;5.50058;-2.41005;,
 2.00120;5.50058;-2.41005;,
 2.00120;5.50058;-2.41005;,
 2.00120;5.50058;-2.41005;,
 2.00120;5.50058;-2.41005;,
 2.00120;5.50058;-2.41005;,
 -4.69059;10.56124;-5.18186;,
 4.73941;10.56124;-5.18186;,
 4.73941;9.56124;-5.18186;,
 -4.69059;9.56124;-5.18186;,
 4.73941;10.56124;-5.18186;,
 4.73941;10.56124;3.36814;,
 4.73941;9.56124;3.36814;,
 4.73941;9.56124;-5.18186;,
 4.73941;10.56124;3.36814;,
 -4.69059;10.56124;3.36814;,
 -4.69059;9.56124;3.36814;,
 4.73941;9.56124;3.36814;,
 -4.69059;10.56124;3.36814;,
 -4.69059;10.56124;-5.18186;,
 -4.69059;9.56124;-5.18186;,
 -4.69059;9.56124;3.36814;,
 4.73941;10.56124;-5.18186;,
 -4.69059;10.56124;-5.18186;,
 -4.69059;9.56124;-5.18186;,
 4.73941;9.56124;-5.18186;,
 -4.69059;14.92419;-2.86510;,
 4.73941;14.92419;-2.86510;,
 4.73941;10.33419;-2.86510;,
 -4.69059;10.33419;-2.86510;,
 4.73941;14.92419;-2.86510;,
 4.73941;14.92419;2.87490;,
 4.73941;10.33419;2.87490;,
 4.73941;10.33419;-2.86510;,
 4.73941;14.92419;2.87490;,
 -4.69059;14.92419;2.87490;,
 -4.69059;10.33419;2.87490;,
 4.73941;10.33419;2.87490;,
 -4.69059;14.92419;2.87490;,
 -4.69059;14.92419;-2.86510;,
 -4.69059;10.33419;-2.86510;,
 -4.69059;10.33419;2.87490;,
 4.73941;14.92419;-2.86510;,
 -4.69059;14.92419;-2.86510;,
 -4.69059;10.33419;-2.86510;,
 4.73941;10.33419;-2.86510;,
 0.05623;13.83481;-3.12849;,
 1.23002;12.66100;-3.12849;,
 -0.00741;11.42358;-3.12849;,
 -1.18121;12.59737;-3.12849;,
 1.23002;12.66100;-3.12849;,
 1.23002;12.66100;-2.73849;,
 -0.00741;11.42358;-2.73849;,
 -0.00741;11.42358;-3.12849;,
 1.23002;12.66100;-2.73849;,
 0.05623;13.83481;-2.73849;,
 -1.18121;12.59737;-2.73849;,
 -0.00741;11.42358;-2.73849;,
 0.05623;13.83481;-2.73849;,
 0.05623;13.83481;-3.12849;,
 -1.18121;12.59737;-3.12849;,
 -1.18121;12.59737;-2.73849;,
 1.23002;12.66100;-3.12849;,
 0.05623;13.83481;-3.12849;,
 -1.18121;12.59737;-3.12849;,
 -0.00741;11.42358;-3.12849;;
 
 152;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 3;20,21,22;,
 3;23,24,21;,
 3;25,26,24;,
 3;27,28,26;,
 3;29,30,28;,
 3;31,32,30;,
 3;33,34,32;,
 3;35,36,34;,
 4;22,21,37,38;,
 4;21,24,39,37;,
 4;24,26,40,39;,
 4;26,28,41,40;,
 4;28,30,42,41;,
 4;30,32,43,42;,
 4;32,34,44,43;,
 4;34,36,45,44;,
 4;38,37,46,47;,
 4;37,39,48,46;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;44,45,54,53;,
 4;47,46,55,56;,
 4;46,48,57,55;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;53,54,63,62;,
 4;56,55,64,65;,
 4;55,57,66,64;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;62,63,72,71;,
 4;65,64,73,74;,
 4;64,66,75,73;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;,
 4;71,72,81,80;,
 4;74,73,82,83;,
 4;73,75,84,82;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;77,78,87,86;,
 4;78,79,88,87;,
 4;79,80,89,88;,
 4;80,81,90,89;,
 3;83,82,91;,
 3;82,84,92;,
 3;84,85,93;,
 3;85,86,94;,
 3;86,87,95;,
 3;87,88,96;,
 3;88,89,97;,
 3;89,90,98;,
 3;99,100,101;,
 3;102,103,100;,
 3;104,105,103;,
 3;106,107,105;,
 3;108,109,107;,
 3;110,111,109;,
 3;112,113,111;,
 3;114,115,113;,
 4;101,100,116,117;,
 4;100,103,118,116;,
 4;103,105,119,118;,
 4;105,107,120,119;,
 4;107,109,121,120;,
 4;109,111,122,121;,
 4;111,113,123,122;,
 4;113,115,124,123;,
 4;117,116,125,126;,
 4;116,118,127,125;,
 4;118,119,128,127;,
 4;119,120,129,128;,
 4;120,121,130,129;,
 4;121,122,131,130;,
 4;122,123,132,131;,
 4;123,124,133,132;,
 4;126,125,134,135;,
 4;125,127,136,134;,
 4;127,128,137,136;,
 4;128,129,138,137;,
 4;129,130,139,138;,
 4;130,131,140,139;,
 4;131,132,141,140;,
 4;132,133,142,141;,
 4;135,134,143,144;,
 4;134,136,145,143;,
 4;136,137,146,145;,
 4;137,138,147,146;,
 4;138,139,148,147;,
 4;139,140,149,148;,
 4;140,141,150,149;,
 4;141,142,151,150;,
 4;144,143,152,153;,
 4;143,145,154,152;,
 4;145,146,155,154;,
 4;146,147,156,155;,
 4;147,148,157,156;,
 4;148,149,158,157;,
 4;149,150,159,158;,
 4;150,151,160,159;,
 4;153,152,161,162;,
 4;152,154,163,161;,
 4;154,155,164,163;,
 4;155,156,165,164;,
 4;156,157,166,165;,
 4;157,158,167,166;,
 4;158,159,168,167;,
 4;159,160,169,168;,
 3;162,161,170;,
 3;161,163,171;,
 3;163,164,172;,
 3;164,165,173;,
 3;165,166,174;,
 3;166,167,175;,
 3;167,168,176;,
 3;168,169,177;,
 4;178,179,180,181;,
 4;182,183,184,185;,
 4;186,187,188,189;,
 4;190,191,192,193;,
 4;190,183,194,195;,
 4;196,197,184,193;,
 4;198,199,200,201;,
 4;202,203,204,205;,
 4;206,207,208,209;,
 4;210,211,212,213;,
 4;210,203,214,215;,
 4;216,217,204,213;,
 4;218,219,220,221;,
 4;222,223,224,225;,
 4;226,227,228,229;,
 4;230,231,232,233;,
 4;230,223,234,235;,
 4;236,237,224,233;;
 
 MeshMaterialList {
  15;
  152;
  11,
  11,
  11,
  11,
  11,
  11,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  14,
  14,
  14,
  14,
  14,
  14;;
  Material {
   0.144000;0.144000;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.075200;0.075200;0.075200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.150400;0.150400;0.150400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.511200;0.511200;0.511200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.288800;0.288800;0.288800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.125600;0.125600;0.125600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.426400;0.426400;0.426400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.228800;0.228800;0.228800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.580000;0.339200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.200800;0.200800;0.200800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.034400;0.106400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.116000;0.106400;0.586400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.778400;0.800000;0.153600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  126;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;-0.000001;,
  0.000000;0.924730;-0.380624;,
  0.269139;0.924732;-0.269139;,
  0.380621;0.924731;-0.000000;,
  0.269142;0.924731;0.269138;,
  -0.000000;0.924731;0.380622;,
  -0.269143;0.924730;0.269138;,
  -0.380624;0.924730;-0.000000;,
  -0.269140;0.924731;-0.269140;,
  0.000000;0.709235;-0.704972;,
  0.498489;0.709236;-0.498490;,
  0.704970;0.709237;-0.000000;,
  0.498492;0.709235;0.498490;,
  -0.000000;0.709234;0.704973;,
  -0.498493;0.709234;0.498490;,
  -0.704972;0.709235;-0.000000;,
  -0.498490;0.709235;-0.498490;,
  0.000000;0.384556;-0.923102;,
  0.652732;0.384555;-0.652732;,
  0.923102;0.384556;-0.000000;,
  0.652732;0.384555;0.652732;,
  0.000000;0.384556;0.923102;,
  -0.652732;0.384555;0.652732;,
  -0.923102;0.384556;-0.000000;,
  -0.652732;0.384555;-0.652732;,
  0.000000;0.000003;-1.000000;,
  0.707107;0.000003;-0.707107;,
  1.000000;0.000003;0.000000;,
  0.707107;0.000003;0.707107;,
  0.000000;0.000003;1.000000;,
  -0.707107;0.000003;0.707107;,
  -1.000000;0.000003;0.000000;,
  -0.707107;0.000003;-0.707107;,
  0.000000;-0.384553;-0.923103;,
  0.652732;-0.384552;-0.652733;,
  0.923103;-0.384553;-0.000000;,
  0.652733;-0.384552;0.652732;,
  0.000000;-0.384553;0.923103;,
  -0.652732;-0.384552;0.652732;,
  -0.923103;-0.384553;-0.000000;,
  -0.652732;-0.384553;-0.652732;,
  -0.000000;-0.709231;-0.704976;,
  0.498493;-0.709232;-0.498492;,
  0.704976;-0.709231;0.000000;,
  0.498496;-0.709229;0.498493;,
  -0.000000;-0.709230;0.704977;,
  -0.498495;-0.709230;0.498493;,
  -0.704976;-0.709231;-0.000000;,
  -0.498494;-0.709231;-0.498494;,
  -0.000000;-0.924737;-0.380607;,
  0.269127;-0.924739;-0.269127;,
  0.380607;-0.924737;0.000000;,
  0.269132;-0.924737;0.269127;,
  -0.000000;-0.924737;0.380606;,
  -0.269131;-0.924737;0.269127;,
  -0.380607;-0.924737;-0.000000;,
  -0.269128;-0.924738;-0.269128;,
  0.000000;-1.000000;-0.000001;,
  0.000002;1.000000;-0.000001;,
  0.000001;0.924731;-0.380622;,
  0.269140;0.924731;-0.269141;,
  0.380623;0.924730;-0.000000;,
  0.269144;0.924730;0.269139;,
  0.000001;0.924731;0.380620;,
  -0.269142;0.924730;0.269142;,
  -0.380622;0.924731;-0.000000;,
  -0.269138;0.924730;-0.269143;,
  0.000001;0.709237;-0.704970;,
  0.498492;0.709236;-0.498487;,
  0.704973;0.709234;-0.000000;,
  0.498494;0.709235;0.498487;,
  0.000001;0.709236;0.704971;,
  -0.498491;0.709236;0.498490;,
  -0.704970;0.709237;-0.000000;,
  -0.498489;0.709236;-0.498491;,
  0.000002;0.384554;-0.923103;,
  0.652735;0.384554;-0.652729;,
  0.923102;0.384554;0.000000;,
  0.652735;0.384554;0.652729;,
  0.000002;0.384554;0.923102;,
  -0.652733;0.384555;0.652730;,
  -0.923103;0.384553;-0.000000;,
  -0.652733;0.384555;-0.652731;,
  0.000003;0.000003;-1.000000;,
  0.707108;0.000003;-0.707106;,
  1.000000;0.000003;0.000000;,
  0.707108;0.000003;0.707106;,
  0.000003;0.000003;1.000000;,
  -0.707108;0.000003;0.707105;,
  -1.000000;0.000003;0.000000;,
  -0.707108;0.000003;-0.707105;,
  0.000002;-0.384551;-0.923104;,
  0.652735;-0.384551;-0.652730;,
  0.923104;-0.384551;0.000000;,
  0.652736;-0.384551;0.652730;,
  0.000002;-0.384551;0.923104;,
  -0.652734;-0.384552;0.652731;,
  -0.923104;-0.384550;-0.000000;,
  -0.652734;-0.384552;-0.652732;,
  0.000001;-0.709233;-0.704974;,
  0.498495;-0.709232;-0.498490;,
  0.704978;-0.709230;-0.000000;,
  0.498498;-0.709230;0.498491;,
  0.000002;-0.709231;0.704976;,
  -0.498494;-0.709231;0.498493;,
  -0.704975;-0.709233;-0.000000;,
  -0.498491;-0.709233;-0.498493;,
  0.000002;-0.924738;-0.380605;,
  0.269129;-0.924737;-0.269129;,
  0.380607;-0.924737;-0.000000;,
  0.269133;-0.924736;0.269129;,
  0.000002;-0.924738;0.380605;,
  -0.269131;-0.924736;0.269131;,
  -0.380606;-0.924737;-0.000000;,
  -0.269126;-0.924737;-0.269131;,
  0.000002;-1.000000;-0.000001;,
  0.707105;-0.707109;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707105;0.707109;0.000000;,
  0.707111;0.707103;0.000000;,
  -0.707105;-0.707109;0.000000;;
  152;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;,
  3;3,5,4;,
  3;3,6,5;,
  3;3,7,6;,
  3;3,8,7;,
  3;3,9,8;,
  3;3,10,9;,
  3;3,11,10;,
  3;3,4,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,4,12,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,12,20,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,20,28,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,28,36,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,36,44,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,44,52,59;,
  3;52,53,60;,
  3;53,54,60;,
  3;54,55,60;,
  3;55,56,60;,
  3;56,57,60;,
  3;57,58,60;,
  3;58,59,60;,
  3;59,52,60;,
  3;61,63,62;,
  3;61,64,63;,
  3;61,65,64;,
  3;61,66,65;,
  3;61,67,66;,
  3;61,68,67;,
  3;61,69,68;,
  3;61,62,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,62,70,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,70,78,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,78,86,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,86,94,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,94,102,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,106,114,113;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,102,110,117;,
  3;110,111,118;,
  3;111,112,118;,
  3;112,113,118;,
  3;113,114,118;,
  3;114,115,118;,
  3;115,116,118;,
  3;116,117,118;,
  3;117,110,118;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;,
  4;0,0,0,0;,
  4;119,119,119,119;,
  4;2,2,2,2;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;125,125,125,125;;
 }
 MeshTextureCoords {
  238;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}