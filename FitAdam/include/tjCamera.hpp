#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/affine.hpp>
#include <iostream>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using std::cout;
namespace tj {

class tjCamera
{
public:
    tjCamera() : m_view(glm::mat4(1.f)), m_projection(glm::mat4(1.f))
    {

    }

    glm::mat4 getViewMatrix() const { return m_view; }


    void setProjectionMatrix(float *p)
    {

        memcpy(glm::value_ptr(m_projection), p, 16 * sizeof(float));

    }

    glm::mat4 getProjectionMatrix() const { return m_projection; }

    void orient(const glm::vec3 &eye, const glm::vec3 &lookAt, const glm::vec3 &up)
    {
        glm::vec3 look = glm::normalize(lookAt-eye);
        glm::vec3 z = -look;
        glm::vec3 x = glm::normalize(glm::cross(up, z));
        glm::vec3 y = glm::cross(z, x);

        glm::mat4 translation = glm::translate(glm::mat4(1.f), -eye);//column major
        glm::mat4 rotation = glm::transpose(glm::mat4( x.x, x.y, x.z, 0,
                                        y.x, y.y, y.z, 0,
                                        z.x, z.y, z.z, 0,
                                            0,     0,     0, 1 ));//column major
        m_view = rotation * translation;

        //both glm and glsl use column-major matrices, but just in memory, you still do the math in regular.
    }



    glm::mat4 m_view, m_projection;


};

}



#endif // CAMERA_H
