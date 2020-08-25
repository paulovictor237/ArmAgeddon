escala=1000;
% scale(escala) import("../visual/welding_torch.stl");
// Append pure shapes (cube, cylinder and sphere), e.g:
// cube([10, 10, 10], center=true);
// cylinder(r=10, h=10, center=true);
// sphere(10);
// coordenadas

x= -0.014515;
y= 0.0528228;
z= 0.00593515;

translate([x*escala+69, y*escala-2, z*escala-40]) {
    rotate([0,0,180]) {
        //cylinder(r=77, h=180, center=false);
        cube([80, 110, 90], center=false);
    }
}
translate([x*escala+69, y*escala-100, z*escala]) {
    rotate([0,0,180]) {
        //cylinder(r=77, h=180, center=false);
        cube([80, 55, 90], center=false);
    }
}
translate([x*escala+69, y*escala-10, z*escala+100]) {
    rotate([-7,0,180]) {
        //cylinder(r=77, h=180, center=false);
        cube([80, 320, 60], center=false);
    }
}
translate([x*escala+45, y*escala-325, z*escala+105]) {
    rotate([-50,0,180]) {
        //cylinder(r=77, h=180, center=false);
        cube([32,143, 32], center=false);
    }
}