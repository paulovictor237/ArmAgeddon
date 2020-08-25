escala=1000;
% scale(escala) import("../visual/link3.stl");

// Append pure shapes (cube, cylinder and sphere), e.g:
// cube([10, 10, 10], center=true);
// cylinder(r=10, h=10, center=true);
// sphere(10);
// coordenadas

x= 1.79739e-15;
y= 0.107891;
z= 0.7407;

translate([x*escala, y*escala-60, z*escala-60]) {
    rotate([0, 0, 0]) {
        cylinder(r=50, h=680, center=false);
    }
}