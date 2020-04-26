# mRTE - mini Ray Tracing Engine


CS403 Computer Graphics, Shanghai Jiao Tong University

![three balls](https://public.noi.top/image/1587879163059.jpeg)

---

## vec3.h
定义了三维向量类 `vec3` ，实现了三维向量的加减乘除、求模、单位向量、点积叉积。

## ray.h
定义了射线类 `ray` ，记录形如 `a + t * b` 的射线，其中 a 是源点坐标，b 是方向向量，t 是大于等于 0 的参数。

## hitable.h
定义了一个抽象类 `hitable` 以及虚函数 `hitable::hit`，表示能与光线碰撞的物体及碰撞方法。

定义了碰撞记录类 `hit_record`，记录碰撞位置的 t 取值、坐标以及法向量。

## sphere.h
定义了 `hitable` 派生的球类 `sphere` ，实现了求球与光线的碰撞记录的方法。

## hitablelist.h
定义了一个碰撞物体列表类 `hitablelist`，记录可与光线碰撞的物体的列表，实现了求光线与这些物体的碰撞记录的方法。

## scamera.h
定义了一个固定的相机类 `camera`，测试用。

## camera.h
定义了一个相机类 `camera`, 实现了视锥构造方法和求视点发出的"光线"的方法。

## material.h
定义了一个抽象类 `material` 以及虚函数 `material::scatter` ，分别表示物体材质及散射方法。

定义了三个 `material` 派生的材质类 `lambertian`, `metal`, `dielectric`，实现了它们的散射方法。

实现了折射函数 `reflect` 和反射函数 `refract` 以及 Schlick 的 Fresnel 近似函数的简化版本 `Schlick`。

## aabb.h
定义了一个轴向包围盒(Axis-Aligned Bounding Box)类 `aabb`，实现了合并两个 `aabb` 的函数 `surrounding_box`。

## bvh.h
定义了一个层次包围盒(Bounding Volume Hierarchy)结点类 `bvh_node`，它是 `hitable` 的派生类，实现了层次包围盒的构造(即结点类的构造方法)。
