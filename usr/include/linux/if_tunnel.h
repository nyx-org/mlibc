#ifndef _LINUX_IF_TUNNEL_H
#define _LINUX_IF_TUNNEL_H

enum {
	IFLA_IPTUN_UNSPEC,
	IFLA_IPTUN_LINK,
	IFLA_IPTUN_LOCAL,
	IFLA_IPTUN_REMOTE,
	IFLA_IPTUN_TTL,
	IFLA_IPTUN_TOS,
	IFLA_IPTUN_ENCAP_LIMIT,
	IFLA_IPTUN_FLOWINFO,
	IFLA_IPTUN_FLAGS,
	IFLA_IPTUN_PROTO,
	IFLA_IPTUN_PMTUDISC,
	IFLA_IPTUN_6RD_PREFIX,
	IFLA_IPTUN_6RD_RELAY_PREFIX,
	IFLA_IPTUN_6RD_PREFIXLEN,
	IFLA_IPTUN_6RD_RELAY_PREFIXLEN,
	IFLA_IPTUN_ENCAP_TYPE,
	IFLA_IPTUN_ENCAP_FLAGS,
	IFLA_IPTUN_ENCAP_SPORT,
	IFLA_IPTUN_ENCAP_DPORT,
	IFLA_IPTUN_COLLECT_METADATA,
	IFLA_IPTUN_FWMARK,
	__IFLA_IPTUN_MAX,
};
#define IFLA_IPTUN_MAX	(__IFLA_IPTUN_MAX - 1)

enum {
	IFLA_GRE_UNSPEC,
	IFLA_GRE_LINK,
	IFLA_GRE_IFLAGS,
	IFLA_GRE_OFLAGS,
	IFLA_GRE_IKEY,
	IFLA_GRE_OKEY,
	IFLA_GRE_LOCAL,
	IFLA_GRE_REMOTE,
	IFLA_GRE_TTL,
	IFLA_GRE_TOS,
	IFLA_GRE_PMTUDISC,
	IFLA_GRE_ENCAP_LIMIT,
	IFLA_GRE_FLOWINFO,
	IFLA_GRE_FLAGS,
	IFLA_GRE_ENCAP_TYPE,
	IFLA_GRE_ENCAP_FLAGS,
	IFLA_GRE_ENCAP_SPORT,
	IFLA_GRE_ENCAP_DPORT,
	IFLA_GRE_COLLECT_METADATA,
	IFLA_GRE_IGNORE_DF,
	IFLA_GRE_FWMARK,
	IFLA_GRE_ERSPAN_INDEX,
	IFLA_GRE_ERSPAN_VER,
	IFLA_GRE_ERSPAN_DIR,
	IFLA_GRE_ERSPAN_HWID,
	__IFLA_GRE_MAX,
};

#define IFLA_GRE_MAX	(__IFLA_GRE_MAX - 1)

enum {
	IFLA_VTI_UNSPEC,
	IFLA_VTI_LINK,
	IFLA_VTI_IKEY,
	IFLA_VTI_OKEY,
	IFLA_VTI_LOCAL,
	IFLA_VTI_REMOTE,
	IFLA_VTI_FWMARK,
	__IFLA_VTI_MAX,
};

#define IFLA_VTI_MAX	(__IFLA_VTI_MAX - 1)

#endif
