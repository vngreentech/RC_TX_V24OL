
#ifndef __VERSION_FIRMWARE__
#define __VERSION_FIRMWARE__

/*================================================
                    VERSION
================================================*/

  /***********************************************
   *    
   * Version: V24OL.1.7
   * Date: 28,Apr,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * 
   * - Fix LỖI: Nhấn giữ nút cancel để lưu các thay 
   * đổi, 1 vài menu không được dùng tính năng này.
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.7")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("28,Apr,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.6
   * Date: 28,Apr,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * 
   * - Design lại các biểu thức điều kiện để tối
   * ưu hoá thuật toán, phương pháp so sánh điều
   * kiện.
   * 
   * - Fix LỖI: Menu Set Throttle Lock, khi bật tắt
   * Switch lock phải giữ thông số của channel
   * Throttle, đúng hướng.
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.6")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("28,Apr,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.5
   * Date: 27,Apr,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * - Hoàn thiện menu Mix channel, fix cứng cho 2
   * channel 1 và 2. Cho phép setup hành trình cho
   * từng channel
   * - Fix LỖI: tại màn hình chính nhấn nút OK để
   * bắt đầu đồng hồ đếm ngược.
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.5")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("27,Apr,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.4
   * Date: 25,Apr,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * - Design lại các menu có chia cột, fix lại
   * vị trí các hàng và cột
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.4")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("25,Apr,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.3
   * Date: 23,Apr,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   *
   * ** Done!
   * - End Point
   * - Set PPM
   * - Get channel limit
   * - Fix tính năng chọn kênh (tần số)
   * - Fix 1 vài lỗi ở round trước
   * - Kiểm tra đánh mã số cho RX, chỉ cho đánh
   * mã 1 lần
   * 
   * **Next:
   * - Map channel
   * - Subtrim
   * - Các feature lớn như: add model, select model,
   * Delete model sẽ được phát triển trong các round 
   * tiếp theo
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.3")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("23,Apr,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.2
   * Date: 03,Apr,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * - Kiểm tra tất cả các peripheral hoạt động OK
   * - Chốt phương án hardware
   * 
   * **Done!
   * - Giao diện và menu chính
   * - Menu version
   * - Menu Reset default
   * - Menu bind RX
   * - Menu reverse
   * - Menu display
   * - Set Pin TX
   * - Set Pin RX
   * - Set Time down
   * - Set throttle lock
   * - Firmware cho RX, 10 channel control, gửi
   * data pin RX về TX
   * - Trên mà hình chính hiển thị pin TX, pin Rx,
   * tần số giữa tx và rx, giá trị Strim của 4 kênh
   * chính, đồng hồ hẹn giờ, thông tin RX.
   * 
   * **Next:
   * - End point
   * - Subtrims
   * - Set PPM
   * - Get channel limit
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.2")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("03,Apr,2024")
  #endif /* RELEASES_DATE */

/*==============================================*/

#endif 
