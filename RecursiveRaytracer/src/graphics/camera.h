#ifndef Camera_h
#define Camera_h

class Camera {
    public:
        Vec3 eye;
        Vec3 center;
        Vec3 up;

        Camera(Vec3 e, Vec3 c, Vec3 u) : eye(e), center(c), up(u) {}
};

#endif