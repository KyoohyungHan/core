/*
   Copyright (C) 2019 MIRACL UK Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.


    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

     https://www.gnu.org/licenses/agpl-3.0.en.html

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   You can be released from the requirements of the license by purchasing
   a commercial license. Buying such a license is mandatory as soon as you
   develop commercial activities involving the MIRACL Core Crypto SDK
   without disclosing the source code of your own applications, or shipping
   the MIRACL Core Crypto SDK with a closed source product.
*/

/* Boneh-Lynn-Shacham signature 256-bit API */

/* Loosely (for now) following https://datatracker.ietf.org/doc/html/draft-irtf-cfrg-bls-signature-00 */

// Minimal-pubkey-size variant

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bls256_ZZZ.h"

using namespace XXX;
using namespace YYY;

#define CEIL(a,b) (((a)-1)/(b)+1)

/* output u[i] \in F_p */
/* https://datatracker.ietf.org/doc/draft-irtf-cfrg-hash-to-curve/ */
static void hash_to_field(int hash,int hlen,FP8 *u,octet *DST,octet *M, int ctr)
{
    int i,j,k,L;
    BIG q,a[8];
    FP2 c,d;
    FP4 e,f;
    DBIG dx;
    char okm[2048],fd[128];
    octet OKM = {0,sizeof(okm),okm};

    BIG_rcopy(q, Modulus);
    L=CEIL(BIG_nbits(q)+CURVE_SECURITY_ZZZ,8);

    XMD_Expand(hash,hlen,&OKM,L*ctr*8,DST,M);
    for (i=0;i<ctr;i++)
    {
        for (k=0;k<8;k++)
        {
            for (j=0;j<L;j++)
                fd[j]=OKM.val[(8*i+k)*L+j];
        
            BIG_dfromBytesLen(dx,fd,L);
            BIG_dmod(a[k],dx,q);
        }
        FP2_from_BIGs(&c,a[0],a[1]);
        FP2_from_BIGs(&d,a[2],a[3]);
        FP4_from_FP2s(&e,&c,&d);

        FP2_from_BIGs(&c,a[4],a[5]);
        FP2_from_BIGs(&d,a[6],a[7]);
        FP4_from_FP2s(&f,&c,&d);

        FP8_from_FP4s(&u[i],&e,&f);
    }
}

/* output u \in F_p 
static void hash_to_base(int hash,int hlen,BIG u,octet *DST,octet *M, int ctr)
{
    int L;
    BIG q;
    DBIG dx;
    char prk[64],okm[128],info[16];
    octet PRK = {0,sizeof(prk),prk};
    octet OKM = {0,sizeof(okm),okm};
    octet INFO = {0,sizeof(info),info};

    BIG_rcopy(q, Modulus);
    L=CEIL(BIG_nbits(q)+CURVE_SECURITY_ZZZ,8);

    OCT_jstring(&INFO,(char *)"H2C");
    OCT_jint(&INFO,ctr,1);
    HKDF_Extract(hash,hlen,&PRK,DST,M);
    HKDF_Expand(hash,hlen,&OKM,L,&PRK,&INFO);

    BIG_dfromBytesLen(dx,OKM.val,L);
    BIG_dmod(u,dx,q);
} */

/* hash a message to an ECP8 point, using SHA2, random oracle method */
static void BLS_HASH_TO_POINT(ECP8 *P, octet *M)
{
    FP8 u[2];
    ECP8 P1;
    char dst[50];
    octet DST = {0,sizeof(dst),dst};

    OCT_jstring(&DST,(char *)"BLS_SIG_ZZZG2_XMD:SHA512-SSWU-RO-_NUL_");
    hash_to_field(MC_SHA2,HASH_TYPE_ZZZ,u,&DST,M,2);

    ECP8_map2point(P,&u[0]);
    ECP8_map2point(&P1,&u[1]);
    ECP8_add(P,&P1);
    ECP8_cfp(P);
    ECP8_affine(P);
}

int ZZZ::BLS_INIT()
{
    return BLS_OK;
}

/* generate key pair, private key S, public key W */
int ZZZ::BLS_KEY_PAIR_GENERATE(octet *IKM, octet* S, octet *W)
{
    int L;
    BIG r,s;
    DBIG dx;
    ECP G;
    char salt[20],prk[HASH_TYPE_ZZZ],okm[128];
    octet SALT = {0,sizeof(salt),salt};
    octet PRK = {0,sizeof(prk),prk};
    octet OKM = {0,sizeof(okm),okm};

    BIG_rcopy(r, CURVE_Order);
    L=CEIL(3*CEIL(BIG_nbits(r),8),2);

    if (!ECP_generator(&G)) return BLS_FAIL;

    OCT_jstring(&SALT,(char *)"BLS-SIG-KEYGEN-SALT-");
    HKDF_Extract(MC_SHA2,HASH_TYPE_ZZZ,&PRK,&SALT,IKM);
    HKDF_Expand(MC_SHA2,HASH_TYPE_ZZZ,&OKM,L,&PRK,NULL);
    BIG_dfromBytesLen(dx,OKM.val,L);
    BIG_dmod(s,dx,r);
    BIG_toBytes(S->val, s);
    S->len = MODBYTES_XXX;
    PAIR_G1mul(&G, s);
    ECP_toOctet(W, &G, true);
    return BLS_OK;
}

/* Sign message M using private key S to produce signature SIG */

int ZZZ::BLS_CORE_SIGN(octet *SIG, octet *M, octet *S)
{
    BIG s;
    ECP8 D;
    BLS_HASH_TO_POINT(&D, M);
    BIG_fromBytes(s, S->val);
    PAIR_G2mul(&D, s);
    ECP8_toOctet(SIG, &D, true); /* compress output */
    return BLS_OK;
}

/* Verify signature of message m, the signature SIG, and the public key W */
int ZZZ::BLS_CORE_VERIFY(octet *SIG, octet *M, octet *W)
{
    FP48 v;
    ECP G, PK;
    ECP8 D, HM;
    BLS_HASH_TO_POINT(&HM, M);

    ECP8_fromOctet(&D, SIG);
	if (!PAIR_G2member(&D)) return BLS_FAIL;
    ECP8_neg(&D);

    ECP_fromOctet(&PK, W);

    if (!ECP_generator(&G)) return BLS_FAIL;
    PAIR_double_ate(&v, &D, &G, &HM, &PK);

    PAIR_fexp(&v);
    if (FP48_isunity(&v)) return BLS_OK;
    return BLS_FAIL;
}

