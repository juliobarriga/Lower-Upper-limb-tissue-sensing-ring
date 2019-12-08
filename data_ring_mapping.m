clc
clear all
close all
%% Aqui se crea el cilindro
[x y z] = cylinder;
%% Aqui se copian los valores obtenidos en el Serial Monitor
anillo = [
0,0,363,431,279;
0,1,227,692,331;
1,0,541,299,499;
1,1,233,374,329;
2,0,372,284,302;
2,1,240,463,240;
]
%% Aqui se transforman los valores de la matriz "anillo" a la matrix 3x6 "datos"
datos = [];
datos(1,1) = anillo(1,3);
datos(1,2) = anillo(2,3);
datos(1,3) = anillo(1,4);
datos(1,4) = anillo(2,4);
datos(1,5) = anillo(1,5);
datos(1,6) = anillo(2,5);
datos(2,1) = anillo(3,3);
datos(2,2) = anillo(4,3);
datos(2,3) = anillo(3,4);
datos(2,4) = anillo(4,4);
datos(2,5) = anillo(3,5);
datos(2,6) = anillo(4,5);
datos(3,1) = anillo(5,3);
datos(3,2) = anillo(6,3);
datos(3,3) = anillo(5,4);
datos(3,4) = anillo(6,4);
datos(3,5) = anillo(5,5);
datos(3,6) = anillo(6,5);
datos
%% Se mapean los colores en el cilinro
surf(x,y,z, 'FaceColor','texturemap','EdgeColor','none','Cdata', datos);
colorbar
