
#ifndef __VERSION_FIRMWARE__
#define __VERSION_FIRMWARE__

/*================================================
                    VERSION
================================================*/

  /***********************************************
   *    
   * Version: V24OL.1.15
   * Date: 11,Jan,2025
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * Fix Bug for RX V24.2
   * 
   * #NOTE: Firmware Update for TX and RX
   * 
   * - Fix LỖI: 
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.15")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("11,Jan,2025")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.14
   * Date: 17,Nov,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * Fix error when disconnect
   * When disconnect with TX, led RX ON and all
   * channel set to 0
   * 
   * #NOTE: Firmware Update for TX and RX
   * 
   * - Fix LỖI: 
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.14")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("17,Nov,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.13
   * Date: 15,Jun,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * Fix power error for RX V24.2
   * 
   * - Fix LỖI: 
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.13")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("15,Jun,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.12
   * Date: 26,May,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * Hoàn thiện menu Subtrim, cho phép Subtrim cho
   * tất cả 10 channel
   * 
   * - Fix LỖI: 
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.12")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("26,May,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.11
   * Date: 11,May,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * 
   * - Fix LỖI: 
   * Mất Info RX: Khi reset default TX thì khi bind
   * lại RX mới bị lỗi không đọc được info rx, dù Rx đã
   * có mã định danh
   * #Lưu ý: Lỗi này được fix trên cả Firmware TX và
   * RX, phải nạp cả 2 Firmware mới
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.11")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("11,May,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.10
   * Date: 11,May,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * - Design lại menu TX battery
   * - Design lại menu RX Battery
   * 
   * - Fix LỖI: 
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.10")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("11,May,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.9
   * Date: 1,May,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * 
   * - Update tính năng map tần số của tính năng Bind RX
   * chỉ ưu tiên các tần số hoạt động ổn định, ít nhiễu
   * trong điều kiện môi trường bình thường
   * 
   * - Update Version mới cho Firmware RX V24.2 . Design
   * lại các structure tối ưu hơn.
   * 
   * - Update Menu set Throttle Lock cho phép set
   * value của CH3 khi Lock: Min, Middle, Max
   * 
   * - Thêm tiếng còi cho các nút Trim của 4 channel
   * chính
   * 
   * - Fix LỖI: 
   *  1. Khi Pin RX xuống dưới mức setup mà tx 
   * và rx mất kết nối thì còi không được hú
   *  2. Fix lỗi ép kiểu của api convert voltage 
   * TX và RX
   * 
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.9")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("1,May,2024")
  #endif /* RELEASES_DATE */

  /***********************************************
   *    
   * Version: V24OL.1.8
   * Date: 29,Apr,2024
   * Dev: NhanNguyen
   * HW-TX: V24OL
   * HW-RX: V24.2
   * 
   * *** Decription ***
   * 
   * - Fix LỖI: Khi nhấn nút trim của 4 channel chính
   * thì có lỗi lưu lại các giá trị cũ của converse,
   * PPM value.
   * 
  ************************************************/
  #ifndef FIRMWARE_VERSION
  #define FIRMWARE_VERSION      ("V24OL.1.8")
  #endif /* FIRMWARE_VERSION */
  #ifndef RELEASES_DATE
  #define RELEASES_DATE         ("29,Apr,2024")
  #endif /* RELEASES_DATE */

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
