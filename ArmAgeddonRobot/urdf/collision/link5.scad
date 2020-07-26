escala=1000;
% scale(escala) import("../visual/link5.stl");
// Append pure shapes (cube, cylinder and sphere), e.g:
// cube([10, 10, 10], center=true);
// cylinder(r=10, h=10, center=true);
// sphere(10);
// coordenadas

x= 1.12684e-07;
y= 0.16389;
z= 1.374;

translate([x*escala, y*escala, z*escala+1]) {
    rotate([0, 0, 0]) {
        cylinder(r=50, h=100, center=false);
    }
}