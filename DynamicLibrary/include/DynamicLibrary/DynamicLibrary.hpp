//
// Created by yaoyu on 2/3/21.
//

#ifndef INC_01_CLIONTEST_DYNAMICLIBRARY_HPP
#define INC_01_CLIONTEST_DYNAMICLIBRARY_HPP

namespace DL
{
    class DynaLib_0 {
    public:
        DynaLib_0() = default;
        ~DynaLib_0() = default;

        void set_int( int v ) { mInt = v; }
        int get_int() const { return mInt; }

        void increase_int();

    private:
        int mInt = 0;
    };
}

#endif //INC_01_CLIONTEST_DYNAMICLIBRARY_HPP
