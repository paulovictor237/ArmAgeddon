escala=1000;
% scale(escala) import("../visual/link4.stl");
// Append pure shapes (cube, cylinder and sphere), e.g:
// cube([10, 10, 10], center=true);
// cylinder(r=10, h=10, center=true);
// sphere(10);
// coordenadas

x= -1.12684e-07;
y= 0.109891;
z= 1.3123;

translate([x*escala, y*escala+55, z*escala-65]) {
    rotate([0, 0, 0]) {
        cylinder(r=50, h=130, center=false);
    }
}