#ifndef A82D0ABC_ABEC_4A0C_AEC9_423B640B0361
#define A82D0ABC_ABEC_4A0C_AEC9_423B640B0361

#include <string>
#include <utility>

namespace z1dg {
    std::string format(const std::string fmt) {
        return fmt;
    }

    template<typename T, typename... Args>
    std::string format(const std::string fmt, T v1, Args&&... args) {
        std::string strfmt = fmt;
        auto placeholder_idx = strfmt.find("{}");
        if (placeholder_idx == std::string::npos) {
            return fmt;
        }
        auto str = strfmt.substr(0, placeholder_idx);
        str += v1;
        str += format(
            strfmt.substr(placeholder_idx+2),
            std::forward<Args>(args)...
        );
        return str;
        // return
        //     strfmt.substr(0, placeholder_idx)
        //     + v1
        //     + format(
        //         strfmt.substr(placeholder_idx+2),
        //         std::forward<Args>(args)...
            // );
    }

}


#endif /* A82D0ABC_ABEC_4A0C_AEC9_423B640B0361 */
