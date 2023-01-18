// Copyright (c) 2019-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <consensus/validation.h>
#include <core_memusage.h>
#include <policy/policy.h>
#include <primitives/transaction.h>
#include <streams.h>
#include <test/fuzz/fuzz.h>
#include <version.h>

FUZZ_TARGET(tx_out)
{
    CDataStream ds(buffer, SER_NETWORK, INIT_PROTO_VERSION);
    CTxOut tx_out;
    try {
        int version;
        ds >> version;
        ds.SetVersion(version);
        ds >> tx_out;
    } catch (const std::ios_base::failure&) {
        return;
    }

    (void)RecursiveDynamicUsage(tx_out);

    (void)tx_out.ToString();
    (void)tx_out.IsNull();
    tx_out.SetNull();
    assert(tx_out.IsNull());
}
