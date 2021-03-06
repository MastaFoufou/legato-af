/**
 * @file le_cfg_simu.c
 *
 * Simulation implementation of the config Tree API.
 *
 * Copyright (C) Sierra Wireless Inc.
 */

#include "legato.h"
#include "mdmCfgEntries.h"

//--------------------------------------------------------------------------------------------------
/**
 * Reference to a tree iterator object.
 */
//--------------------------------------------------------------------------------------------------
typedef struct le_cfg_Iterator* le_cfg_IteratorRef_t;

//--------------------------------------------------------------------------------------------------
/**
 * Simulated config tree values.
 */
//--------------------------------------------------------------------------------------------------
static bool MessageCounting = true;
static int32_t RxMessageCount = 0;
static int32_t TxMessageCount = 0;
static int32_t RxCbMessageCount = 0;
static bool StatusReportActivation = false;

//--------------------------------------------------------------------------------------------------
/**
 * Config tree iterator reference
 */
//--------------------------------------------------------------------------------------------------
static le_cfg_IteratorRef_t SimuIteratorRef = NULL;

//--------------------------------------------------------------------------------------------------
/**
 * Length of the strings used by this API.
 */
//--------------------------------------------------------------------------------------------------
#define LE_CFG_STR_LEN          511

//--------------------------------------------------------------------------------------------------
/**
 * Connect the current client thread to the service providing this API (STUBBED FUNCTION)
 */
//--------------------------------------------------------------------------------------------------
void le_cfg_ConnectService
(
    void
)
{
    return;
}

//--------------------------------------------------------------------------------------------------
/**
 * Create a read transaction and open a new iterator for traversing the config tree.
 *
 * @note This action creates a read lock on the given tree, which will start a read-timeout.
 *        Once the read timeout expires, all active read iterators on that tree will be
 *        expired and the clients will be killed.
 *
 * @note A tree transaction is global to that tree; a long-held read transaction will block other
 *        user's write transactions from being committed.
 *
 * @return This will return a newly created iterator reference.
 */
//--------------------------------------------------------------------------------------------------
le_cfg_IteratorRef_t le_cfg_CreateReadTxn
(
    const char* basePath    ///< [IN] Path to the location to create the new iterator.
)
{
    return (le_cfg_IteratorRef_t)SimuIteratorRef;
}

//--------------------------------------------------------------------------------------------------
/**
 * Create a write transaction and open a new iterator for both reading and writing.
 *
 * @note This action creates a write transaction. If the app holds the iterator for
 *        longer than the configured write transaction timeout, the iterator will cancel the
 *        transaction. Other reads will fail to return data, and all writes will be thrown
 *        away.
 *
 * @note A tree transaction is global to that tree; a long-held write transaction will block
 *       other user's write transactions from being started. Other trees in the system
 *       won't be affected.
 *
 * @return This will return a newly created iterator reference.
 */
//--------------------------------------------------------------------------------------------------
le_cfg_IteratorRef_t le_cfg_CreateWriteTxn
(
    const char* basePath    ///< [IN] Path to the location to create the new iterator.
)
{
    return (le_cfg_IteratorRef_t)SimuIteratorRef;
}

//--------------------------------------------------------------------------------------------------
/**
 * Close the write iterator and commit the write transaction. This updates the config tree
 * with all of the writes that occurred using the iterator.
 *
 * @note This operation will also delete the iterator object.
 */
//--------------------------------------------------------------------------------------------------
void le_cfg_CommitTxn
(
    le_cfg_IteratorRef_t iteratorRef    ///< [IN] Iterator object to commit.
)
{
    return;
}

//--------------------------------------------------------------------------------------------------
/**
 * Close and free the given iterator object. If the iterator is a write iterator, the transaction
 * will be canceled. If the iterator is a read iterator, the transaction will be closed.
 *
 * @note This operation will also delete the iterator object.
 */
//--------------------------------------------------------------------------------------------------
void le_cfg_CancelTxn
(
    le_cfg_IteratorRef_t iteratorRef    ///< [IN] Iterator object to close.
)
{
    return;
}

//--------------------------------------------------------------------------------------------------
/**
 * Set a simulated integer value for a specific node.
 */
//--------------------------------------------------------------------------------------------------
void le_cfgSimu_SetIntNodeValue
(
    le_cfg_IteratorRef_t iteratorRef,   ///< [IN] Iterator to use as a basis for the transaction.
    const char* path,                   ///< [IN] Path to the target node. Can be an absolute path,
                                        ///<      or a path relative from the iterator's current
                                        ///<      position.
    int32_t value                       ///< [IN] Value to write.
)
{
    SimuIteratorRef = iteratorRef;

    if (0 == strncmp(path, CFG_NODE_RX_COUNT, strlen(CFG_NODE_RX_COUNT)))
    {
        RxMessageCount = value;
    }
    else if (0 == strncmp(path, CFG_NODE_TX_COUNT, strlen(CFG_NODE_TX_COUNT)))
    {
        TxMessageCount = value;
    }
    else if (0 == strncmp(path, CFG_NODE_RX_CB_COUNT, strlen(CFG_NODE_RX_CB_COUNT)))
    {
        RxCbMessageCount = value;
    }
    else
    {
        LE_ERROR("Unsupported path '%s'", path);
    }
}

//--------------------------------------------------------------------------------------------------
/**
 * Set a simulated boolean value for a specific node.
 */
//--------------------------------------------------------------------------------------------------
void le_cfgSimu_SetBoolNodeValue
(
    le_cfg_IteratorRef_t iteratorRef,   ///< [IN] Iterator to use as a basis for the transaction.
    const char* path,                   ///< [IN] Path to the target node. Can be an absolute path,
                                        ///<      or a path relative from the iterator's current
                                        ///<      position.
    bool value                          ///< [IN] Value to write.
)
{
    SimuIteratorRef = iteratorRef;

    if (0 == strncmp(path, CFG_NODE_COUNTING, strlen(CFG_NODE_COUNTING)))
    {
        MessageCounting = value;
    }
    else if (0 == strncmp(path, CFG_NODE_STATUS_REPORT, strlen(CFG_NODE_STATUS_REPORT)))
    {
        StatusReportActivation = value;
    }
    else
    {
        LE_ERROR("Unsupported path '%s'", path);
    }
}

//--------------------------------------------------------------------------------------------------
/**
 * Read a signed integer value from the config tree.
 *
 * If the underlying value is not an integer, the default value will be returned instead. The
 * default value is also returned if the node does not exist or if it's empty.
 *
 * If the value is a floating point value, then it will be rounded and returned as an integer.
 *
 * Valid for both read and write transactions.
 *
 * If the path is empty, the iterator's current node will be read.
 */
//--------------------------------------------------------------------------------------------------
int32_t le_cfg_GetInt
(
    le_cfg_IteratorRef_t iteratorRef,   ///< [IN] Iterator to use as a basis for the transaction.
    const char* path,                   ///< [IN] Path to the target node. Can be an absolute path,
                                        ///<      or a path relative from the iterator's current
                                        ///<      position
    int32_t defaultValue                ///< [IN] Default value to use if the original can't be
                                        ///<      read.
)
{
    int32_t value;

    if (0 == strncmp(path, CFG_NODE_RX_COUNT, strlen(CFG_NODE_RX_COUNT)))
    {
        value = RxMessageCount;
    }
    else if (0 == strncmp(path, CFG_NODE_TX_COUNT, strlen(CFG_NODE_TX_COUNT)))
    {
        value = TxMessageCount;
    }
    else if (0 == strncmp(path, CFG_NODE_RX_CB_COUNT, strlen(CFG_NODE_RX_CB_COUNT)))
    {
        value = RxCbMessageCount;
    }
    else
    {
        value = defaultValue;
        LE_ERROR("Unsupported path '%s', using default value %d", path, defaultValue);
    }

    return value;
}

//--------------------------------------------------------------------------------------------------
/**
 * Write a signed integer value to the config tree. Only valid during a
 * write transaction.
 *
 * If the path is empty, the iterator's current node will be set.
 */
//--------------------------------------------------------------------------------------------------
void le_cfg_SetInt
(
    le_cfg_IteratorRef_t iteratorRef,   ///< [IN] Iterator to use as a basis for the transaction.
    const char* path,                   ///< [IN] Path to the target node. Can be an absolute path,
                                        ///<      or a path relative from the iterator's current
                                        ///<      position
    int32_t value                       ///< [IN] Value to write.
)
{
    le_cfgSimu_SetIntNodeValue(iteratorRef, path, value);
}

//--------------------------------------------------------------------------------------------------
/**
 * Read a value from the tree as a boolean. If the node is empty or doesn't exist, the default
 * value is returned. Default value is also returned if the node is a different type than
 * expected.
 *
 * Valid for both read and write transactions.
 *
 * If the path is empty, the iterator's current node will be read.
 */
//--------------------------------------------------------------------------------------------------
bool le_cfg_GetBool
(
    le_cfg_IteratorRef_t iteratorRef,   ///< [IN] Iterator to use as a basis for the transaction.
    const char* path,                   ///< [IN] Path to the target node. Can be an absolute path,
                                        ///<      or a path relative from the iterator's current
                                        ///<      position
    bool defaultValue                   ///< [IN] Default value to use if the original can't be
                                        ///<      read.
)
{
    bool value;

    if (0 == strncmp(path, CFG_NODE_COUNTING, strlen(CFG_NODE_COUNTING)))
    {
        value = MessageCounting;
    }
    else if (0 == strncmp(path, CFG_NODE_STATUS_REPORT, strlen(CFG_NODE_STATUS_REPORT)))
    {
        value = StatusReportActivation;
    }
    else
    {
        value = defaultValue;
        LE_ERROR("Unsupported path '%s', using default value %d", path, defaultValue);
    }

    return value;
}

//--------------------------------------------------------------------------------------------------
/**
 * Write a boolean value to the config tree. Only valid during a write
 * transaction.
 *
 * If the path is empty, the iterator's current node will be set.
 */
//--------------------------------------------------------------------------------------------------
void le_cfg_SetBool
(
    le_cfg_IteratorRef_t iteratorRef,   ///< [IN] Iterator to use as a basis for the transaction.
    const char* path,                   ///< [IN] Path to the target node. Can be an absolute path,
                                        ///<      or a path relative from the iterator's current
                                        ///<      position
    bool value                          ///< [IN] Value to write.
)
{
    le_cfgSimu_SetBoolNodeValue(iteratorRef, path, value);
}
