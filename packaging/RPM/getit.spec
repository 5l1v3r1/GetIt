Name:			getit
Version:		3.0
Release:		1%{?dist}
Summary:		Send HTTP requests to your API endpoints

License:		GPLv3+
URL:			https://getit.bartkessels.net
Source0:		https://github.com/bartkessels/%{name}/archive/%{version}/%{name}-%{version}.tar.gz

BuildRequires:	gcc
BuildRequires:	autoconf
BuildRequires:	automake
BuildRequires:	gtk3-devel
BuildRequires:	gtksourceview3-devel
BuildRequires:	json-glib-devel
BuildRequires:	glib-devel
BuildRequires:	libsoup-devel
BuildRequires:	libnotify-devel

Requires:		gtk3
Requires:		gtksourceview3
Requires:		json-glib
Requires:		glib
Requires:		libsoup
Requires:		libnotify

%description
Application to send HTTP requests to test your own API endpoints

%global debug_package %{nil}

%prep
%autosetup -p1

%build
autoreconf --install
%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
%make_install

%files
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop

%changelog
* Tue Jul 11 2017 Bart Kessels <bartkessels@bk-mail.com> 3.0
- Rewrite application to C

* Sat Jun 17 2017 Bart Kessels <bartkessels@outlook.com> 2.0-1
- Display message when something has wrong while sending the request
- Add ability to save a request
- Add ability to open a request
- Add ability to clear the current request

* Sun Jun 11 2017 Bart Kessels <bartkessels@outlook.com> 1.4.1-1
- Add cancel request button
- Add shortcuts for send and cancel button
- Display notification when request is processed

* Fri Jun 9 2017 Bart Kessels <bartkessels@outlook.com> 1.4-1
- Add spinner to indicate the request is still being sent
- Add shortcut to send request

* Thu Jun 1 2017 Bart Kessels <bartkessels@outlook.com> 1.3-1
- Refactor codebase
- Add ability to create raw body instead of form-data

* Fri Apr 7 2017 Bart Kessels <bartkessels@outlook.com> 1.2-1
- Add ability to add cookies to a requests
- Fix endless scrolling bug on response stack

* Fri Mar 31 2017 Bart Kessels <bartkessels@outlook.com> 1.1-1
- Add ability to add files to request

* Wed Mar 29 2017 Bart Kessels <bartkessels@outlook.com> - 1.0-1
- Initial Packaging
