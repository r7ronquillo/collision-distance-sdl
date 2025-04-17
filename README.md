# 2D AABB Collision Detection with SDL

## Overview
This project is a simple 2D AABB (Axis-Aligned Bounding Box) collision detection program written in **C** using the **Simple DirectMedia Layer (SDL)** library. It includes:
- **Point-in-Box Collision:** Detects if the mouse cursor is inside a rectangle.
- **Box-in-Box Collision:** Detects if two rectangles overlap.
- **Distance Calculations:** Calculates the distance between the mouse and a fixed box, as well as the distance between two moving boxes.
- **Real-Time Interaction:** One rectangle follows the mouse, with an option to toggle this behavior.

![demo](https://github.com/user-attachments/assets/9445c5e6-c975-4831-ac59-62db0cf2d91c)

## Dependencies
This project requires **SDL3** for rendering, input handling, and window management.

**Installing SDL:**
- Visit the official SDL website: [https://github.com/libsdl-org/SDL](https://github.com/libsdl-org/SDL)

**Note:** This project uses SDL3 and was built using the C17 standard. Development and testing were performed on Windows 11 with Visual Studio 2022. Compatibility with other platforms (Linux, macOS) has not been tested.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
