// In der Entwicklerkonsole des Browsers auf der Seite des Geraets ausfuehren (F12 > Konsole), mit der Sprache auf DE.
// Listet alle Texte der Seite auf, die in eine Sprachdatei gehoeren (Schluessel); mit Sprache EN zeigt es, was noch unuebersetzt ist.
// Run in the developer console of the browser on the page of the device (F12 > console), with the language set to DE.
// Lists all texts of the page that belong in a language file (keys); with language EN it shows what is still untranslated.

(function () {
  var SKIP = /^(SCRIPT|STYLE|CODE|PRE|TEXTAREA|SVG)$/, INL = /^(CODE|EM|STRONG|B|KBD)$/, ATTR = ['title', 'placeholder', 'aria-label', 'label'];
  var LET = /[A-Za-zÄÖÜäöüß]/;
  function norm(s) { return s.replace(/\s+/g, ' ').trim(); }
  var keys = [], seen = {};
  function add(k) {
    if (!k || !LET.test(k)) return;
    if (typeof UI_HOST === 'string' && UI_HOST) k = k.split(UI_HOST).join('{host}');
    if (seen[k]) return;
    seen[k] = 1;
    keys.push(k);
  }
  function inlineMixed(e) {
    var el = 0, tx = 0;
    for (var c = e.firstChild; c; c = c.nextSibling) {
      if (c.nodeType === 1) {
        if (!INL.test(c.nodeName.toUpperCase()) || c.id || c.querySelector('[id]')) return 0;
        el = 1;
      } else if (c.nodeType === 3) {
        if (LET.test(c.nodeValue)) tx = 1;
      } else if (c.nodeType !== 8) return 0;
    }
    return el && tx;
  }
  function walk(n) {
    if (n.nodeType === 3) {
      var p = n.parentNode;
      if (p && SKIP.test(p.nodeName.toUpperCase())) return;
      add(norm(n.nodeValue));
      return;
    }
    if (n.nodeType !== 1 || SKIP.test(n.nodeName.toUpperCase())) return;
    ATTR.forEach(function (a) { if (n.hasAttribute(a)) add(norm(n.getAttribute(a))); });
    if (inlineMixed(n)) { add(norm(n.innerHTML)); return; }
    for (var c = n.firstChild; c; c = c.nextSibling) walk(c);
  }
  walk(document.body);
  add(norm(document.title));
  console.log(keys.length + ' Texte / texts');
  console.log(JSON.stringify(keys, null, 1));
  return keys;
})();
