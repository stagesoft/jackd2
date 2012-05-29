#/bin/sh
#
# Little helper script to generate the jackd2 tarball from a git
# repository.
#
# Example usage:
#    $ git clone git://github.com/jackaudio/jack2.git
#    $ cd jack2
#    $ sh /path/to/make_tarball.sh /tmp/jackd2-x.y.z

GIT_SHORT_VERSION=`git diff-tree HEAD | head -n 1 | cut -b -8`
DATE_STRING=`date "+%Y%m%d"`
TARGET_DIR="$1+${DATE_STRING}git${GIT_SHORT_VERSION}"

if [ $# -ne 1 ]; then
    echo "Usage: $0 <path-prefix>"
    exit 1
fi

echo "Creating ${TARGET_DIR}"
mkdir "${TARGET_DIR}" || exit 1

echo "Exporting jack to ${TARGET_DIR}"
git archive master | tar -C "${TARGET_DIR}" -xf -

echo "Cleaning git files from export directory"
find "${TARGET_DIR}" -name ".git*" -delete

# replace waf by waf-light
echo "Replacying waf by waf-light"
( cd "${TARGET_DIR}" && \
    ./waf ; \
    mv .waf*/waflib waflib && \
    rm waf ; \
    find ./waflib -iname "*.pyc" -delete ; \
    wget http://waf.googlecode.com/git-history/waf-1.6.11/waf-light ; \
    ln -s waf-light waf && chmod +x waf-light
)

# make it DFSG clean
echo "Making it DFSG clean"
rm -rf "${TARGET_DIR}/windows" "${TARGET_DIR}/macosx"

# create final tarball
echo "Creating tarball"
tar -C "${TARGET_DIR}/../" -cvzf "${TARGET_DIR}".tar.gz \
    "`basename "${TARGET_DIR}"`" && echo "All done. Enjoy."
