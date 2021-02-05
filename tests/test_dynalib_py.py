
import numpy as np

import DynaLib_py

if __name__ == '__main__':

    de = DynaLib_py.DynaEigen()

    a64 = np.random.rand( 3, 2 ).astype(np.float64)
    print('a64 = \n{}'.format(a64))
    de.change_through_reference(a64)
    print('a64 = \n{}'.format(a64))

    a32 = np.random.rand( 3, 2 ).astype(np.float32)
    print('a32 = \n{}'.format(a32))
    de.change_through_reference(a32)
    print('a32 = \n{}'.format(a32))

    # Get a NumPy array from an Eigen matrix.
    b = de.return_matrix_by_value()
    b[0, 0] = 0
    print('b = \n{}'.format(b))
    print('b.flags.writeable = {}'.format(b.flags.writeable))
    print('b.flags.owndata = {}'.format(b.flags.owndata))
    print('b.flags = {}'.format(b.flags))
