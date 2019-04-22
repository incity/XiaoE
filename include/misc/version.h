#ifndef __VERSION_H__
#define __VERSION_H__

/** XIAOE_MAJOR_VERSION
  * XiaoE major version
  *
  * @note 99 is default value for development version (master branch)
  */
#define XIAOE_MAJOR_VERSION  99

/** XIAOE_MINOR_VERSION
  * XiaoE minor version
  *
  * @note 99 is default value for development version (master branch)
  */
#define XIAOE_MINOR_VERSION  99

/** XIAOE_PATCH_VERSION
  * XiaoE patch version
  *
  * @note 99 is default value for development version (master branch)
  */
#define XIAOE_PATCH_VERSION  99

#define XIAOE_ENCODE_VERSION(major, minor, patch) ((major)*10000 + (minor)*100 + (patch))

/** XIAOE_VERSION
  * XiaoE version (MMmmpp - M(Major); m(minor); p(patch))
  *
  * @note 999999 is default value for development version (master branch)
  */
#define XIAOE_VERSION XIAOE_ENCODE_VERSION(XIAOE_MAJOR_VERSION, XIAOE_MINOR_VERSION, XIAOE_PATCH_VERSION)

/** XIAOE_VERSION_CHECK
  * Macro can be used to check minimum XiaoE version required for feature/library. If current version
  * is less than required, it will assert.
  *
  * @note: Version of master branch will be 999999 as default, hence no assert/warning is provided for
  * master branch code
  */
#define XIAOE_VERSION_CHECK(major, minor, patch) do { \
                                       XIAOE_STATIC_ASSERT((XIAOE_VERSION >= XIAOE_ENCODE_VERSION((major),(minor),(patch))), "Incompatible XiaoE version detected!!"); \
                                     } while(0)

#endif    /* __VERSION_H__ */

