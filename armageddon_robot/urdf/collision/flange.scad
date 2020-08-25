escala=1000;
% scale(escala) import("../visual/flange.stl");

// Append pure shapes (cube, cylinder and sphere), e.g:
// cube([10, 10, 10], center=true);
// cylinder(r=10, h=10, center=true);
// sphere(10);
// coordenadas

x=1.05754e-14;
y=0.225591;
z=1.428;

translate([x*escala, y*escala+1, z*escala]) {
    rotate([-90, 0, 0]) {
        cylinder(r=46, h=22, center=false);
    }
}