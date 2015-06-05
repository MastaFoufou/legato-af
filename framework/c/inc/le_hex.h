/**
 * @page c_hex Hex string API
 *
 *
 * @ref le_hex.h "API Reference"
 *
 * <HR>
 *
 *
 * This API provides convertion tools to switch between:
 *  - @ref le_hex_StringToBinary  Hex-String to binary
 *  - @ref le_hex_BinaryToString  Binary to Hex-String
 *
 *
 * @section hex_conversion Conversion
 *
 * Code sample:
 *
 * @code
 * char     HexString[] = "136ABC";
 * uint8_t  binString[] = {0x13,0x6A,0xBC};
 * @endcode
 *
 * So @ref le_hex_StringToBinary will convert HexString to binString.
 *
 * and @ref le_hex_BinaryToString will convert binString to HexString.
 *
 *
 *
 * <HR>
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */


/** @file le_hex.h
 *
 * Legato @ref c_hex include file.
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */

#ifndef LEGATO_HEX_INCLUDE_GUARD
#define LEGATO_HEX_INCLUDE_GUARD


//--------------------------------------------------------------------------------------------------
/**
 * Converts hex string to binary format.
 *
 * @return size of binary, if < 0 it has failed
 */
//--------------------------------------------------------------------------------------------------
int32_t le_hex_StringToBinary
(
    const char *stringPtr,     ///< [IN] string to convert, terminated with '\0'.
    uint32_t    stringLength,  ///< [IN] string length
    uint8_t    *binaryPtr,     ///< [OUT] binary result
    uint32_t    binarySize     ///< [IN] size of the binary table
);

//--------------------------------------------------------------------------------------------------
/**
 * Converts binary to hex string format.
 *
 * @return size of hex string, if < 0 it has failed
 */
//--------------------------------------------------------------------------------------------------
int32_t le_hex_BinaryToString
(
    const uint8_t *binaryPtr,  ///< [IN] binary array to convert
    uint32_t       binarySize, ///< [IN] size of binary array
    char          *stringPtr,  ///< [OUT] hex string array, terminated with '\0'.
    uint32_t       stringSize  ///< [IN] size of string array
);

//--------------------------------------------------------------------------------------------------
/**
 * This function convert hexa string into integer
 *
 * @return
 *      \return return the value or -1 if not possible.
 */
//--------------------------------------------------------------------------------------------------
int le_hex_HexaToInteger(char s[]);

#endif // LEGATO_HEX_INCLUDE_GUARD
