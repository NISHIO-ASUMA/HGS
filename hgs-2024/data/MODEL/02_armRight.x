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
 232;
 -2.39319;2.78374;0.20524;,
 -2.04811;2.65750;-0.49215;,
 -2.36158;2.66212;-0.57295;,
 -2.39319;2.78374;0.20524;,
 -1.79462;2.65338;-0.29083;,
 -2.39319;2.78374;0.20524;,
 -1.64491;2.65049;-0.00379;,
 -2.39319;2.78374;0.20524;,
 -1.62489;2.64932;0.31933;,
 -2.39319;2.78374;0.20524;,
 -1.73802;2.65007;0.62267;,
 -2.39319;2.78374;0.20524;,
 -1.96472;2.65261;0.85376;,
 -2.39319;2.78374;0.20524;,
 -2.26582;2.65651;0.97266;,
 -2.39319;2.78374;0.20524;,
 -2.58923;2.66109;0.95881;,
 -2.39319;2.78374;0.20524;,
 -2.87905;2.66555;0.81460;,
 -2.39319;2.78374;0.20524;,
 -3.08515;2.66914;0.56497;,
 -2.39319;2.78374;0.20524;,
 -3.17191;2.67121;0.25307;,
 -2.39319;2.78374;0.20524;,
 -3.12431;2.67143;-0.06715;,
 -2.39319;2.78374;0.20524;,
 -2.95060;2.66975;-0.34034;,
 -2.39319;2.78374;0.20524;,
 -2.68081;2.66645;-0.51925;,
 -2.39319;2.78374;0.20524;,
 -2.36158;2.66212;-0.57295;,
 -1.74028;2.29701;-1.12195;,
 -2.33652;2.30580;-1.27564;,
 -1.25809;2.28918;-0.73901;,
 -0.97334;2.28368;-0.19303;,
 -0.93527;2.28145;0.42159;,
 -1.15045;2.28288;0.99856;,
 -1.58167;2.28772;1.43813;,
 -2.15438;2.29513;1.66429;,
 -2.76956;2.30384;1.63794;,
 -3.32081;2.31234;1.36364;,
 -3.71285;2.31915;0.88880;,
 -3.87786;2.32310;0.29555;,
 -3.78733;2.32351;-0.31356;,
 -3.45692;2.32031;-0.83319;,
 -2.94373;2.31404;-1.17350;,
 -2.33652;2.30580;-1.27564;,
 -1.49981;1.73757;-1.62252;,
 -2.32048;1.74967;-1.83405;,
 -0.83614;1.72680;-1.09545;,
 -0.44422;1.71923;-0.34397;,
 -0.39182;1.71616;0.50198;,
 -0.68798;1.71812;1.29612;,
 -1.28152;1.72478;1.90113;,
 -2.06978;1.73499;2.21242;,
 -2.91649;1.74697;2.17616;,
 -3.67524;1.75867;1.79860;,
 -4.21482;1.76804;1.14505;,
 -4.44195;1.77348;0.32850;,
 -4.31735;1.77405;-0.50987;,
 -3.86256;1.76964;-1.22508;,
 -3.15623;1.76102;-1.69347;,
 -2.32048;1.74967;-1.83405;,
 -1.35026;1.03394;-1.94485;,
 -2.31501;1.04816;-2.19352;,
 -0.57008;1.02128;-1.32524;,
 -0.10935;1.01237;-0.44183;,
 -0.04774;1.00876;0.55264;,
 -0.39590;1.01107;1.48621;,
 -1.09364;1.01891;2.19745;,
 -2.02031;1.03090;2.56339;,
 -3.01567;1.04499;2.52075;,
 -3.90762;1.05874;2.07692;,
 -4.54195;1.06976;1.30862;,
 -4.80895;1.07615;0.34871;,
 -4.66248;1.07682;-0.63686;,
 -4.12784;1.07163;-1.47762;,
 -3.29750;1.06150;-2.02826;,
 -2.31501;1.04816;-2.19352;,
 -1.30626;0.25500;-2.05740;,
 -2.32065;0.26996;-2.31887;,
 -0.48592;0.24169;-1.40591;,
 -0.00148;0.23233;-0.47703;,
 0.06330;0.22853;0.56861;,
 -0.30278;0.23096;1.55022;,
 -1.03643;0.23920;2.29807;,
 -2.01078;0.25181;2.68284;,
 -3.05738;0.26662;2.63802;,
 -3.99523;0.28108;2.17134;,
 -4.66220;0.29267;1.36350;,
 -4.22678;0.29464;-1.56614;,
 -4.78893;0.30009;-0.68209;,
 -3.35370;0.28398;-2.14510;,
 -2.32065;0.26996;-2.31887;,
 -1.37211;-0.52301;-1.94915;,
 -2.33686;-0.50879;-2.19782;,
 -0.59193;-0.53567;-1.32953;,
 -0.13120;-0.54458;-0.44613;,
 -0.06959;-0.54819;0.54835;,
 -0.41776;-0.54587;1.48191;,
 -1.11549;-0.53804;2.19315;,
 -2.04216;-0.52605;2.55909;,
 -3.03753;-0.51196;2.51646;,
 -3.92948;-0.49821;2.07262;,
 -4.56380;-0.48719;1.30432;,
 -4.14969;-0.48532;-1.48192;,
 -4.68433;-0.48013;-0.64115;,
 -3.31935;-0.49545;-2.03255;,
 -2.33686;-0.50879;-2.19782;,
 -1.54138;-1.22394;-1.63069;,
 -2.36204;-1.21184;-1.84222;,
 -0.87771;-1.23471;-1.10362;,
 -0.48579;-1.24228;-0.35214;,
 -0.43338;-1.24535;0.49380;,
 -0.72955;-1.24339;1.28795;,
 -1.32309;-1.23672;1.89296;,
 -2.11135;-1.22652;2.20425;,
 -2.95806;-1.21453;2.16798;,
 -3.71681;-1.20284;1.79043;,
 -4.25639;-1.19347;1.13688;,
 -4.83081;-0.48079;0.34441;,
 -4.48352;-1.18802;0.32033;,
 -4.35892;-1.18746;-0.51804;,
 -3.90412;-1.19187;-1.23325;,
 -3.19780;-1.20049;-1.70164;,
 -2.36204;-1.21184;-1.84222;,
 -1.79749;-1.77916;-1.13320;,
 -2.39374;-1.77037;-1.28688;,
 -1.31531;-1.78699;-0.75025;,
 -1.03056;-1.79249;-0.20428;,
 -0.99248;-1.79472;0.41034;,
 -1.20767;-1.79329;0.98731;,
 -1.63888;-1.78845;1.42689;,
 -2.21160;-1.78104;1.65305;,
 -2.82677;-1.77233;1.62670;,
 -3.37803;-1.76384;1.35240;,
 -3.77006;-1.75702;0.87756;,
 -3.93508;-1.75307;0.28430;,
 -3.84454;-1.75266;-0.32481;,
 -3.51413;-1.75586;-0.84444;,
 -3.00095;-1.76213;-1.18475;,
 -2.39374;-1.77037;-1.28688;,
 -2.11537;-2.13433;-0.50537;,
 -2.42884;-2.12971;-0.58617;,
 -1.86187;-2.13844;-0.30405;,
 -1.71217;-2.14134;-0.01701;,
 -1.69216;-2.14251;0.30611;,
 -1.80528;-2.14176;0.60945;,
 -2.03198;-2.13921;0.84054;,
 -2.33308;-2.13532;0.95944;,
 -2.65649;-2.13074;0.94559;,
 -2.94631;-2.12627;0.80138;,
 -3.15241;-2.12269;0.55175;,
 -3.23917;-2.12061;0.23985;,
 -3.19157;-2.12040;-0.08038;,
 -3.01786;-2.12208;-0.35356;,
 -2.74807;-2.12537;-0.53247;,
 -2.42884;-2.12971;-0.58617;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -2.46391;-2.25468;0.19134;,
 -3.51448;0.24105;-1.65969;,
 -3.52068;-0.52866;-1.54768;,
 -11.59491;-0.47269;-1.50514;,
 -11.58872;0.29703;-1.61714;,
 -3.52587;-1.17354;-1.11280;,
 -11.60009;-1.11756;-1.07025;,
 -3.52902;-1.56585;-0.44118;,
 -11.60326;-1.50988;-0.39863;,
 -3.52951;-1.62792;0.33416;,
 -11.60374;-1.57194;0.37671;,
 -3.52724;-1.34740;1.05965;,
 -11.60149;-1.29143;1.10220;,
 -3.52267;-0.77991;1.59160;,
 -11.59691;-0.72394;1.63414;,
 -3.51669;-0.03783;1.82465;,
 -11.59093;0.01815;1.86719;,
 -3.51051;0.73190;1.71264;,
 -11.58473;0.78786;1.75520;,
 -3.50529;1.37678;1.27777;,
 -11.57955;1.43274;1.32031;,
 -3.50217;1.76907;0.60615;,
 -11.57639;1.82505;0.64869;,
 -3.50167;1.83113;-0.16919;,
 -11.57591;1.88712;-0.12665;,
 -3.50393;1.55064;-0.89469;,
 -11.57818;1.60662;-0.85214;,
 -3.50850;0.98314;-1.42664;,
 -11.58275;1.03912;-1.38409;,
 -3.51448;0.24105;-1.65969;,
 -11.58872;0.29703;-1.61714;,
 -3.51559;0.10162;0.08249;,
 -3.52068;-0.52866;-1.54768;,
 -3.52587;-1.17354;-1.11280;,
 -3.52902;-1.56585;-0.44118;,
 -3.52951;-1.62792;0.33416;,
 -3.52724;-1.34740;1.05965;,
 -3.52267;-0.77991;1.59160;,
 -3.51669;-0.03783;1.82465;,
 -3.51051;0.73190;1.71264;,
 -3.50529;1.37678;1.27777;,
 -3.50217;1.76907;0.60615;,
 -3.50167;1.83113;-0.16919;,
 -3.50393;1.55064;-0.89469;,
 -3.50850;0.98314;-1.42664;,
 -11.58983;0.15759;0.12503;,
 -11.58872;0.29703;-1.61714;,
 -11.59491;-0.47269;-1.50514;,
 -11.60009;-1.11756;-1.07025;,
 -11.60326;-1.50988;-0.39863;,
 -11.60374;-1.57194;0.37671;,
 -11.60149;-1.29143;1.10220;,
 -11.59691;-0.72394;1.63414;,
 -11.59093;0.01815;1.86719;,
 -11.58473;0.78786;1.75520;,
 -11.57955;1.43274;1.32031;,
 -11.57639;1.82505;0.64869;,
 -11.57591;1.88712;-0.12665;,
 -11.57818;1.60662;-0.85214;,
 -11.58275;1.03912;-1.38409;;
 
 188;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 3;23,24,22;,
 3;25,26,24;,
 3;27,28,26;,
 3;29,30,28;,
 4;2,1,31,32;,
 4;1,4,33,31;,
 4;4,6,34,33;,
 4;6,8,35,34;,
 4;8,10,36,35;,
 4;10,12,37,36;,
 4;12,14,38,37;,
 4;14,16,39,38;,
 4;16,18,40,39;,
 4;18,20,41,40;,
 4;20,22,42,41;,
 4;22,24,43,42;,
 4;24,26,44,43;,
 4;26,28,45,44;,
 4;28,30,46,45;,
 4;32,31,47,48;,
 4;31,33,49,47;,
 4;33,34,50,49;,
 4;34,35,51,50;,
 4;35,36,52,51;,
 4;36,37,53,52;,
 4;37,38,54,53;,
 4;38,39,55,54;,
 4;39,40,56,55;,
 4;40,41,57,56;,
 4;41,42,58,57;,
 4;42,43,59,58;,
 4;43,44,60,59;,
 4;44,45,61,60;,
 4;45,46,62,61;,
 4;48,47,63,64;,
 4;47,49,65,63;,
 4;49,50,66,65;,
 4;50,51,67,66;,
 4;51,52,68,67;,
 4;52,53,69,68;,
 4;53,54,70,69;,
 4;54,55,71,70;,
 4;55,56,72,71;,
 4;56,57,73,72;,
 4;57,58,74,73;,
 4;58,59,75,74;,
 4;59,60,76,75;,
 4;60,61,77,76;,
 4;61,62,78,77;,
 4;64,63,79,80;,
 4;63,65,81,79;,
 4;65,66,82,81;,
 4;66,67,83,82;,
 4;67,68,84,83;,
 4;68,69,85,84;,
 4;69,70,86,85;,
 4;70,71,87,86;,
 4;71,72,88,87;,
 4;72,73,89,88;,
 4;75,76,90,91;,
 4;76,77,92,90;,
 4;77,78,93,92;,
 4;80,79,94,95;,
 4;79,81,96,94;,
 4;81,82,97,96;,
 4;82,83,98,97;,
 4;83,84,99,98;,
 4;84,85,100,99;,
 4;85,86,101,100;,
 4;86,87,102,101;,
 4;87,88,103,102;,
 4;88,89,104,103;,
 4;91,90,105,106;,
 4;90,92,107,105;,
 4;92,93,108,107;,
 4;95,94,109,110;,
 4;94,96,111,109;,
 4;96,97,112,111;,
 4;97,98,113,112;,
 4;98,99,114,113;,
 4;99,100,115,114;,
 4;100,101,116,115;,
 4;101,102,117,116;,
 4;102,103,118,117;,
 4;103,104,119,118;,
 4;104,120,121,119;,
 4;120,106,122,121;,
 4;106,105,123,122;,
 4;105,107,124,123;,
 4;107,108,125,124;,
 4;110,109,126,127;,
 4;109,111,128,126;,
 4;111,112,129,128;,
 4;112,113,130,129;,
 4;113,114,131,130;,
 4;114,115,132,131;,
 4;115,116,133,132;,
 4;116,117,134,133;,
 4;117,118,135,134;,
 4;118,119,136,135;,
 4;119,121,137,136;,
 4;121,122,138,137;,
 4;122,123,139,138;,
 4;123,124,140,139;,
 4;124,125,141,140;,
 4;127,126,142,143;,
 4;126,128,144,142;,
 4;128,129,145,144;,
 4;129,130,146,145;,
 4;130,131,147,146;,
 4;131,132,148,147;,
 4;132,133,149,148;,
 4;133,134,150,149;,
 4;134,135,151,150;,
 4;135,136,152,151;,
 4;136,137,153,152;,
 4;137,138,154,153;,
 4;138,139,155,154;,
 4;139,140,156,155;,
 4;140,141,157,156;,
 3;143,142,158;,
 3;142,144,159;,
 3;144,145,160;,
 3;145,146,161;,
 3;146,147,162;,
 3;147,148,163;,
 3;148,149,164;,
 3;149,150,165;,
 3;150,151,166;,
 3;151,152,167;,
 3;152,153,168;,
 3;153,154,169;,
 3;154,155,170;,
 3;155,156,171;,
 3;156,157,172;,
 4;173,174,175,176;,
 4;174,177,178,175;,
 4;177,179,180,178;,
 4;179,181,182,180;,
 4;181,183,184,182;,
 4;183,185,186,184;,
 4;185,187,188,186;,
 4;187,189,190,188;,
 4;189,191,192,190;,
 4;191,193,194,192;,
 4;193,195,196,194;,
 4;195,197,198,196;,
 4;197,199,200,198;,
 4;199,201,202,200;,
 3;203,204,173;,
 3;203,205,204;,
 3;203,206,205;,
 3;203,207,206;,
 3;203,208,207;,
 3;203,209,208;,
 3;203,210,209;,
 3;203,211,210;,
 3;203,212,211;,
 3;203,213,212;,
 3;203,214,213;,
 3;203,215,214;,
 3;203,216,215;,
 3;203,173,216;,
 3;217,218,219;,
 3;217,219,220;,
 3;217,220,221;,
 3;217,221,222;,
 3;217,222,223;,
 3;217,223,224;,
 3;217,224,225;,
 3;217,225,226;,
 3;217,226,227;,
 3;217,227,228;,
 3;217,228,229;,
 3;217,229,230;,
 3;217,230,231;,
 3;217,231,218;;
 
 MeshMaterialList {
  2;
  188;
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
  0;;
  Material {
   0.621176;0.621176;0.621176;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  180;
  0.014034;0.999898;0.002760;,
  0.026562;0.951724;-0.305804;,
  0.150867;0.949892;-0.273761;,
  0.251382;0.948259;-0.193938;,
  0.310734;0.947113;-0.080131;,
  0.318674;0.946648;0.047999;,
  0.273816;0.946946;0.168282;,
  0.183922;0.947954;0.259916;,
  0.064541;0.949499;0.307060;,
  -0.063701;0.951315;0.301565;,
  -0.178614;0.953085;0.244387;,
  -0.260338;0.954507;0.145396;,
  -0.294746;0.955329;0.021720;,
  -0.275875;0.955415;-0.105238;,
  -0.206987;0.954749;-0.213568;,
  -0.100008;0.953441;-0.284515;,
  0.036510;0.810503;-0.584596;,
  0.272999;0.807016;-0.523637;,
  0.464244;0.803913;-0.371754;,
  0.577181;0.801731;-0.155206;,
  0.592286;0.800845;0.088570;,
  0.506940;0.801411;0.317416;,
  0.335902;0.803330;0.491763;,
  0.108752;0.806272;0.581463;,
  -0.135237;0.809727;0.571011;,
  -0.353883;0.813096;0.462215;,
  -0.509378;0.815797;0.273879;,
  -0.574830;0.817363;0.038575;,
  -0.538924;0.817527;-0.203003;,
  -0.407868;0.816258;-0.409105;,
  -0.204322;0.813772;-0.544084;,
  0.042888;0.589880;-0.806352;,
  0.368493;0.585078;-0.722424;,
  0.631813;0.580804;-0.513302;,
  0.787315;0.577797;-0.215142;,
  0.808107;0.576579;0.120496;,
  0.690597;0.577361;0.435580;,
  0.455104;0.580005;0.675629;,
  0.142351;0.584055;0.799134;,
  -0.193589;0.588810;0.784746;,
  -0.494631;0.593448;0.634948;,
  -0.708721;0.597168;0.375640;,
  -0.798834;0.599328;0.051667;,
  -0.749397;0.599553;-0.280962;,
  -0.568957;0.597801;-0.564732;,
  -0.288707;0.594381;-0.750573;,
  0.045066;0.311331;-0.949232;,
  0.427940;0.305686;-0.850543;,
  0.737574;0.300660;-0.604638;,
  0.920424;0.297127;-0.254038;,
  0.944875;0.295694;0.140631;,
  0.806699;0.296611;0.511135;,
  0.529785;0.299720;0.793408;,
  0.162021;0.304481;0.938637;,
  -0.233006;0.310073;0.921717;,
  -0.586995;0.315530;0.745572;,
  -0.787833;0.367830;0.493984;,
  -0.882842;0.466273;0.056390;,
  -0.842616;0.371037;-0.390294;,
  -0.674393;0.320646;-0.665117;,
  -0.344855;0.316624;-0.883643;,
  0.042824;0.002158;-0.999080;,
  0.445446;-0.003779;-0.895301;,
  0.771045;-0.009064;-0.636716;,
  0.963324;-0.012778;-0.268038;,
  0.989035;-0.014286;0.146986;,
  0.843734;-0.013324;0.536596;,
  0.552542;-0.010056;0.833425;,
  0.165813;-0.005048;0.986144;,
  -0.249587;0.000834;0.968352;,
  -0.621833;0.006569;0.783123;,
  -0.771042;0.009066;0.636719;,
  -0.843731;0.013323;-0.536601;,
  -0.713735;0.011950;-0.700314;,
  -0.367204;0.007721;-0.930109;,
  0.036382;-0.307232;-0.950939;,
  0.419262;-0.312878;-0.852248;,
  0.728893;-0.317902;-0.606345;,
  0.911741;-0.321436;-0.255748;,
  0.936192;-0.322868;0.138926;,
  0.798015;-0.321950;0.509431;,
  0.521104;-0.318843;0.791700;,
  0.153342;-0.314083;0.936930;,
  -0.241690;-0.308494;0.920010;,
  -0.595680;-0.303038;0.743864;,
  -0.797885;-0.348290;0.492010;,
  -0.895585;-0.441615;0.053884;,
  -0.852667;-0.345085;-0.392271;,
  -0.683074;-0.297920;-0.666824;,
  -0.353538;-0.301942;-0.885348;,
  0.026377;-0.586394;-0.809596;,
  0.351984;-0.591197;-0.725667;,
  0.615304;-0.595467;-0.516546;,
  0.770803;-0.598472;-0.218391;,
  0.791596;-0.599690;0.117249;,
  0.674086;-0.598911;0.432336;,
  0.438596;-0.596266;0.672384;,
  0.125841;-0.592218;0.795891;,
  -0.210102;-0.587462;0.781502;,
  -0.511143;-0.582822;0.631705;,
  -0.725231;-0.579103;0.372397;,
  -0.815346;-0.576947;0.048420;,
  -0.765907;-0.576724;-0.284212;,
  -0.585467;-0.578471;-0.567978;,
  -0.305221;-0.581891;-0.753818;,
  0.013794;-0.807974;-0.589057;,
  0.250280;-0.811462;-0.528100;,
  0.441525;-0.814565;-0.376218;,
  0.554464;-0.816747;-0.159669;,
  0.569566;-0.817631;0.084105;,
  0.484220;-0.817065;0.312947;,
  0.313189;-0.815144;0.487291;,
  0.086034;-0.812203;0.576995;,
  -0.157958;-0.808749;0.566547;,
  -0.376601;-0.805381;0.457747;,
  -0.532093;-0.802679;0.269414;,
  -0.597544;-0.801110;0.034112;,
  -0.561637;-0.800948;-0.207477;,
  -0.430585;-0.802219;-0.413572;,
  -0.227044;-0.804705;-0.548544;,
  -0.000134;-0.950396;-0.311042;,
  0.124167;-0.952228;-0.279006;,
  0.224675;-0.953859;-0.199186;,
  0.284030;-0.955007;-0.085371;,
  0.291972;-0.955471;0.042755;,
  0.247115;-0.955173;0.163029;,
  0.157228;-0.954164;0.254658;,
  0.037843;-0.952620;0.301799;,
  -0.090402;-0.950804;0.296308;,
  -0.205313;-0.949034;0.239128;,
  -0.287034;-0.947613;0.140147;,
  -0.321436;-0.946788;0.016481;,
  -0.302562;-0.946703;-0.110496;,
  -0.233680;-0.947371;-0.218819;,
  -0.126713;-0.948677;-0.289750;,
  -0.014036;-0.999898;-0.002759;,
  -0.004699;0.079848;-0.996796;,
  -0.007414;-0.360538;-0.932715;,
  -0.008661;-0.729531;-0.683893;,
  -0.008193;-0.954027;-0.299609;,
  -0.006101;-0.989554;0.144037;,
  -0.002801;-0.829072;0.559134;,
  0.001053;-0.504407;0.863465;,
  0.004699;-0.079852;0.996796;,
  0.007414;0.360530;0.932718;,
  0.008660;0.729534;0.683890;,
  0.008193;0.954029;0.299601;,
  0.006102;0.989555;-0.144024;,
  0.002802;0.829078;-0.559125;,
  -0.001053;0.504405;-0.863467;,
  0.999968;-0.008051;-0.000010;,
  -0.999968;0.008049;0.000010;,
  0.999968;-0.008055;-0.000008;,
  0.999968;-0.008056;-0.000008;,
  0.999968;-0.008052;-0.000010;,
  0.999968;-0.008050;-0.000012;,
  0.999968;-0.008050;-0.000014;,
  0.999968;-0.008048;-0.000012;,
  0.999968;-0.008050;-0.000011;,
  0.999968;-0.008042;-0.000012;,
  0.999968;-0.008059;-0.000000;,
  0.999968;-0.008060;-0.000018;,
  0.999968;-0.008041;-0.000023;,
  0.999968;-0.008048;-0.000001;,
  0.999968;-0.008049;-0.000003;,
  0.999968;-0.008052;-0.000006;,
  -0.999968;0.008042;0.000007;,
  -0.999968;0.008040;0.000007;,
  -0.999968;0.008048;-0.000002;,
  -0.999968;0.008052;0.000006;,
  -0.999968;0.008044;0.000009;,
  -0.999968;0.008049;0.000003;,
  -0.999968;0.008055;0.000014;,
  -0.999968;0.008056;0.000013;,
  -0.999968;0.008051;0.000016;,
  -0.999968;0.008052;0.000010;,
  -0.999968;0.008055;0.000014;,
  -0.999968;0.008051;0.000021;,
  -0.999968;0.008048;0.000012;,
  -0.999968;0.008044;0.000007;;
  188;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,1,15;,
  4;1,2,17,16;,
  4;2,3,18,17;,
  4;3,4,19,18;,
  4;4,5,20,19;,
  4;5,6,21,20;,
  4;6,7,22,21;,
  4;7,8,23,22;,
  4;8,9,24,23;,
  4;9,10,25,24;,
  4;10,11,26,25;,
  4;11,12,27,26;,
  4;12,13,28,27;,
  4;13,14,29,28;,
  4;14,15,30,29;,
  4;15,1,16,30;,
  4;16,17,32,31;,
  4;17,18,33,32;,
  4;18,19,34,33;,
  4;19,20,35,34;,
  4;20,21,36,35;,
  4;21,22,37,36;,
  4;22,23,38,37;,
  4;23,24,39,38;,
  4;24,25,40,39;,
  4;25,26,41,40;,
  4;26,27,42,41;,
  4;27,28,43,42;,
  4;28,29,44,43;,
  4;29,30,45,44;,
  4;30,16,31,45;,
  4;31,32,47,46;,
  4;32,33,48,47;,
  4;33,34,49,48;,
  4;34,35,50,49;,
  4;35,36,51,50;,
  4;36,37,52,51;,
  4;37,38,53,52;,
  4;38,39,54,53;,
  4;39,40,55,54;,
  4;40,41,56,55;,
  4;41,42,57,56;,
  4;42,43,58,57;,
  4;43,44,59,58;,
  4;44,45,60,59;,
  4;45,31,46,60;,
  4;46,47,62,61;,
  4;47,48,63,62;,
  4;48,49,64,63;,
  4;49,50,65,64;,
  4;50,51,66,65;,
  4;51,52,67,66;,
  4;52,53,68,67;,
  4;53,54,69,68;,
  4;54,55,70,69;,
  4;55,56,71,70;,
  4;58,59,73,72;,
  4;59,60,74,73;,
  4;60,46,61,74;,
  4;61,62,76,75;,
  4;62,63,77,76;,
  4;63,64,78,77;,
  4;64,65,79,78;,
  4;65,66,80,79;,
  4;66,67,81,80;,
  4;67,68,82,81;,
  4;68,69,83,82;,
  4;69,70,84,83;,
  4;70,71,85,84;,
  4;72,73,88,87;,
  4;73,74,89,88;,
  4;74,61,75,89;,
  4;75,76,91,90;,
  4;76,77,92,91;,
  4;77,78,93,92;,
  4;78,79,94,93;,
  4;79,80,95,94;,
  4;80,81,96,95;,
  4;81,82,97,96;,
  4;82,83,98,97;,
  4;83,84,99,98;,
  4;84,85,100,99;,
  4;85,86,101,100;,
  4;86,87,102,101;,
  4;87,88,103,102;,
  4;88,89,104,103;,
  4;89,75,90,104;,
  4;90,91,106,105;,
  4;91,92,107,106;,
  4;92,93,108,107;,
  4;93,94,109,108;,
  4;94,95,110,109;,
  4;95,96,111,110;,
  4;96,97,112,111;,
  4;97,98,113,112;,
  4;98,99,114,113;,
  4;99,100,115,114;,
  4;100,101,116,115;,
  4;101,102,117,116;,
  4;102,103,118,117;,
  4;103,104,119,118;,
  4;104,90,105,119;,
  4;105,106,121,120;,
  4;106,107,122,121;,
  4;107,108,123,122;,
  4;108,109,124,123;,
  4;109,110,125,124;,
  4;110,111,126,125;,
  4;111,112,127,126;,
  4;112,113,128,127;,
  4;113,114,129,128;,
  4;114,115,130,129;,
  4;115,116,131,130;,
  4;116,117,132,131;,
  4;117,118,133,132;,
  4;118,119,134,133;,
  4;119,105,120,134;,
  3;120,121,135;,
  3;121,122,135;,
  3;122,123,135;,
  3;123,124,135;,
  3;124,125,135;,
  3;125,126,135;,
  3;126,127,135;,
  3;127,128,135;,
  3;128,129,135;,
  3;129,130,135;,
  3;130,131,135;,
  3;131,132,135;,
  3;132,133,135;,
  3;133,134,135;,
  3;134,120,135;,
  4;136,137,137,136;,
  4;137,138,138,137;,
  4;138,139,139,138;,
  4;139,140,140,139;,
  4;140,141,141,140;,
  4;141,142,142,141;,
  4;142,143,143,142;,
  4;143,144,144,143;,
  4;144,145,145,144;,
  4;145,146,146,145;,
  4;146,147,147,146;,
  4;147,148,148,147;,
  4;148,149,149,148;,
  4;149,136,136,149;,
  3;150,152,153;,
  3;150,154,152;,
  3;150,155,154;,
  3;150,156,155;,
  3;150,157,156;,
  3;150,158,157;,
  3;150,159,158;,
  3;150,160,159;,
  3;150,161,160;,
  3;150,162,161;,
  3;150,163,162;,
  3;150,164,163;,
  3;150,165,164;,
  3;150,153,165;,
  3;151,166,167;,
  3;151,167,168;,
  3;151,168,169;,
  3;151,169,170;,
  3;151,170,171;,
  3;151,171,172;,
  3;151,172,173;,
  3;151,173,174;,
  3;151,174,175;,
  3;151,175,176;,
  3;151,176,177;,
  3;151,177,178;,
  3;151,178,179;,
  3;151,179,166;;
 }
 MeshTextureCoords {
  232;
  0.033330;0.000000;,
  0.066670;0.100000;,
  0.000000;0.100000;,
  0.100000;0.000000;,
  0.133330;0.100000;,
  0.166670;0.000000;,
  0.200000;0.100000;,
  0.233330;0.000000;,
  0.266670;0.100000;,
  0.300000;0.000000;,
  0.333330;0.100000;,
  0.366670;0.000000;,
  0.400000;0.100000;,
  0.433330;0.000000;,
  0.466670;0.100000;,
  0.500000;0.000000;,
  0.533330;0.100000;,
  0.566670;0.000000;,
  0.600000;0.100000;,
  0.633330;0.000000;,
  0.666670;0.100000;,
  0.700000;0.000000;,
  0.733330;0.100000;,
  0.766670;0.000000;,
  0.800000;0.100000;,
  0.833330;0.000000;,
  0.866670;0.100000;,
  0.900000;0.000000;,
  0.933330;0.100000;,
  0.966670;0.000000;,
  1.000000;0.100000;,
  0.066670;0.200000;,
  0.000000;0.200000;,
  0.133330;0.200000;,
  0.200000;0.200000;,
  0.266670;0.200000;,
  0.333330;0.200000;,
  0.400000;0.200000;,
  0.466670;0.200000;,
  0.533330;0.200000;,
  0.600000;0.200000;,
  0.666670;0.200000;,
  0.733330;0.200000;,
  0.800000;0.200000;,
  0.866670;0.200000;,
  0.933330;0.200000;,
  1.000000;0.200000;,
  0.066670;0.300000;,
  0.000000;0.300000;,
  0.133330;0.300000;,
  0.200000;0.300000;,
  0.266670;0.300000;,
  0.333330;0.300000;,
  0.400000;0.300000;,
  0.466670;0.300000;,
  0.533330;0.300000;,
  0.600000;0.300000;,
  0.666670;0.300000;,
  0.733330;0.300000;,
  0.800000;0.300000;,
  0.866670;0.300000;,
  0.933330;0.300000;,
  1.000000;0.300000;,
  0.066670;0.400000;,
  0.000000;0.400000;,
  0.133330;0.400000;,
  0.200000;0.400000;,
  0.266670;0.400000;,
  0.333330;0.400000;,
  0.400000;0.400000;,
  0.466670;0.400000;,
  0.533330;0.400000;,
  0.600000;0.400000;,
  0.666670;0.400000;,
  0.733330;0.400000;,
  0.800000;0.400000;,
  0.866670;0.400000;,
  0.933330;0.400000;,
  1.000000;0.400000;,
  0.066670;0.500000;,
  0.000000;0.500000;,
  0.133330;0.500000;,
  0.200000;0.500000;,
  0.266670;0.500000;,
  0.333330;0.500000;,
  0.400000;0.500000;,
  0.466670;0.500000;,
  0.533330;0.500000;,
  0.600000;0.500000;,
  0.666670;0.500000;,
  0.866670;0.500000;,
  0.800000;0.500000;,
  0.933330;0.500000;,
  1.000000;0.500000;,
  0.066670;0.600000;,
  0.000000;0.600000;,
  0.133330;0.600000;,
  0.200000;0.600000;,
  0.266670;0.600000;,
  0.333330;0.600000;,
  0.400000;0.600000;,
  0.466670;0.600000;,
  0.533330;0.600000;,
  0.600000;0.600000;,
  0.666670;0.600000;,
  0.866670;0.600000;,
  0.800000;0.600000;,
  0.933330;0.600000;,
  1.000000;0.600000;,
  0.066670;0.700000;,
  0.000000;0.700000;,
  0.133330;0.700000;,
  0.200000;0.700000;,
  0.266670;0.700000;,
  0.333330;0.700000;,
  0.400000;0.700000;,
  0.466670;0.700000;,
  0.533330;0.700000;,
  0.600000;0.700000;,
  0.666670;0.700000;,
  0.733330;0.600000;,
  0.733330;0.700000;,
  0.800000;0.700000;,
  0.866670;0.700000;,
  0.933330;0.700000;,
  1.000000;0.700000;,
  0.066670;0.800000;,
  0.000000;0.800000;,
  0.133330;0.800000;,
  0.200000;0.800000;,
  0.266670;0.800000;,
  0.333330;0.800000;,
  0.400000;0.800000;,
  0.466670;0.800000;,
  0.533330;0.800000;,
  0.600000;0.800000;,
  0.666670;0.800000;,
  0.733330;0.800000;,
  0.800000;0.800000;,
  0.866670;0.800000;,
  0.933330;0.800000;,
  1.000000;0.800000;,
  0.066670;0.900000;,
  0.000000;0.900000;,
  0.133330;0.900000;,
  0.200000;0.900000;,
  0.266670;0.900000;,
  0.333330;0.900000;,
  0.400000;0.900000;,
  0.466670;0.900000;,
  0.533330;0.900000;,
  0.600000;0.900000;,
  0.666670;0.900000;,
  0.733330;0.900000;,
  0.800000;0.900000;,
  0.866670;0.900000;,
  0.933330;0.900000;,
  1.000000;0.900000;,
  0.033330;1.000000;,
  0.100000;1.000000;,
  0.166670;1.000000;,
  0.233330;1.000000;,
  0.300000;1.000000;,
  0.366670;1.000000;,
  0.433330;1.000000;,
  0.500000;1.000000;,
  0.566670;1.000000;,
  0.633330;1.000000;,
  0.700000;1.000000;,
  0.766670;1.000000;,
  0.833330;1.000000;,
  0.900000;1.000000;,
  0.966670;1.000000;,
  0.000000;0.000000;,
  0.071430;0.000000;,
  0.071430;1.000000;,
  0.000000;1.000000;,
  0.142860;0.000000;,
  0.142860;1.000000;,
  0.214290;0.000000;,
  0.214290;1.000000;,
  0.285710;0.000000;,
  0.285710;1.000000;,
  0.357140;0.000000;,
  0.357140;1.000000;,
  0.428570;0.000000;,
  0.428570;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.571430;0.000000;,
  0.571430;1.000000;,
  0.642860;0.000000;,
  0.642860;1.000000;,
  0.714290;0.000000;,
  0.714290;1.000000;,
  0.785710;0.000000;,
  0.785710;1.000000;,
  0.857140;0.000000;,
  0.857140;1.000000;,
  0.928570;0.000000;,
  0.928570;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}