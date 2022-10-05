![1.jpg](1.jpg)

![2.jpg](2.jpg)

[![Watch the video](https://img.youtube.com/vi/_sGzVKS0liw/maxresdefault.jpg)](https://youtube.com/shorts/_sGzVKS0liw?feature=share)

[![Watch the video](https://img.youtube.com/vi/ijRxG0WvWfA/maxresdefault.jpg)](https://youtube.com/shorts/ijRxG0WvWfA?feature=share)

[![Watch the video](https://img.youtube.com/vi/9owT0PD85F0/maxresdefault.jpg)](https://youtube.com/shorts/9owT0PD85F0?feature=share)

<pre>
<font color="#5e6d03">#include</font> <font color="#434f54">&lt;</font><font color="#000000">EnableInterrupt</font><font color="#434f54">.</font><font color="#000000">h</font><font color="#434f54">&gt;</font>

<font color="#5e6d03">#define</font> <font color="#000000">SERIAL_PORT_SPEED</font> <font color="#000000">9600</font>
<font color="#5e6d03">#define</font> <font color="#000000">RC_NUM_CHANNELS</font> &nbsp;<font color="#000000">4</font>

<font color="#5e6d03">#define</font> <font color="#000000">RC_CH1</font> &nbsp;<font color="#000000">0</font>
<font color="#5e6d03">#define</font> <font color="#000000">RC_CH2</font> &nbsp;<font color="#000000">1</font>
<font color="#5e6d03">#define</font> <font color="#000000">RC_CH3</font> &nbsp;<font color="#000000">2</font>
<font color="#5e6d03">#define</font> <font color="#000000">RC_CH4</font> &nbsp;<font color="#000000">3</font>

<font color="#5e6d03">#define</font> <font color="#000000">RC_CH1_PIN</font> &nbsp;<font color="#000000">8</font>
<font color="#5e6d03">#define</font> <font color="#000000">RC_CH2_PIN</font> &nbsp;<font color="#000000">7</font>
<font color="#5e6d03">#define</font> <font color="#000000">RC_CH3_PIN</font> &nbsp;<font color="#000000">4</font>
<font color="#5e6d03">#define</font> <font color="#000000">RC_CH4_PIN</font> &nbsp;<font color="#000000">2</font>

<font color="#00979c">uint16_t</font> <font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_NUM_CHANNELS</font><font color="#000000">]</font><font color="#000000">;</font>
<font color="#00979c">uint32_t</font> <font color="#000000">rc_start</font><font color="#000000">[</font><font color="#000000">RC_NUM_CHANNELS</font><font color="#000000">]</font><font color="#000000">;</font>
<font color="#00979c">volatile</font> <font color="#00979c">uint16_t</font> <font color="#000000">rc_shared</font><font color="#000000">[</font><font color="#000000">RC_NUM_CHANNELS</font><font color="#000000">]</font><font color="#000000">;</font>

<font color="#00979c">unsigned</font> <font color="#00979c">long</font> <font color="#000000">previousMillis</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font> &nbsp;
<font color="#00979c">const</font> <font color="#00979c">long</font> <font color="#000000">interval</font> <font color="#434f54">=</font> <font color="#000000">10000</font><font color="#000000">;</font>
<font color="#00979c">const</font> <font color="#00979c">long</font> <font color="#000000">intervalShort</font> <font color="#434f54">=</font> <font color="#000000">100</font><font color="#000000">;</font><font color="#434f54">&#47;&#47; interval at which to blink (milliseconds)</font>
<font color="#00979c">int</font> <font color="#000000">ARLPM1</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#00979c">int</font> <font color="#000000">ARLPM2</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#00979c">int</font> <font color="#000000">ARRRM1</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#00979c">int</font> <font color="#000000">ARRRM2</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>

<font color="#00979c">int</font> <font color="#000000">LPM1</font> <font color="#434f54">=</font> <font color="#000000">3</font><font color="#000000">;</font>
<font color="#00979c">int</font> <font color="#000000">LPM2</font> <font color="#434f54">=</font> <font color="#000000">9</font><font color="#000000">;</font>
<font color="#00979c">int</font> <font color="#000000">RRM1</font> <font color="#434f54">=</font> <font color="#000000">10</font><font color="#000000">;</font>
<font color="#00979c">int</font> <font color="#000000">RRM2</font> <font color="#434f54">=</font> <font color="#000000">11</font><font color="#000000">;</font>

<font color="#00979c">void</font> <font color="#000000">rc_read_values</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#d35400">noInterrupts</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">memcpy</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#434f54">,</font> <font color="#000000">(</font><font color="#00979c">const</font> <font color="#00979c">void</font> <font color="#434f54">*</font><font color="#000000">)</font><font color="#000000">rc_shared</font><font color="#434f54">,</font> <font color="#00979c">sizeof</font><font color="#000000">(</font><font color="#000000">rc_shared</font><font color="#000000">)</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">interrupts</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#000000">calc_input</font><font color="#000000">(</font><font color="#00979c">uint8_t</font> <font color="#000000">channel</font><font color="#434f54">,</font> <font color="#00979c">uint8_t</font> <font color="#000000">input_pin</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#d35400">digitalRead</font><font color="#000000">(</font><font color="#000000">input_pin</font><font color="#000000">)</font> <font color="#434f54">==</font> <font color="#00979c">HIGH</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">rc_start</font><font color="#000000">[</font><font color="#000000">channel</font><font color="#000000">]</font> <font color="#434f54">=</font> <font color="#d35400">micros</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">}</font> <font color="#5e6d03">else</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#00979c">uint16_t</font> <font color="#000000">rc_compare</font> <font color="#434f54">=</font> <font color="#000000">(</font><font color="#00979c">uint16_t</font><font color="#000000">)</font><font color="#000000">(</font><font color="#d35400">micros</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#434f54">-</font> <font color="#000000">rc_start</font><font color="#000000">[</font><font color="#000000">channel</font><font color="#000000">]</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">rc_shared</font><font color="#000000">[</font><font color="#000000">channel</font><font color="#000000">]</font> <font color="#434f54">=</font> <font color="#000000">rc_compare</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">}</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#000000">calc_ch1</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">calc_input</font><font color="#000000">(</font><font color="#000000">RC_CH1</font><font color="#434f54">,</font> <font color="#000000">RC_CH1_PIN</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>
<font color="#00979c">void</font> <font color="#000000">calc_ch2</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">calc_input</font><font color="#000000">(</font><font color="#000000">RC_CH2</font><font color="#434f54">,</font> <font color="#000000">RC_CH2_PIN</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>
<font color="#00979c">void</font> <font color="#000000">calc_ch3</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">calc_input</font><font color="#000000">(</font><font color="#000000">RC_CH3</font><font color="#434f54">,</font> <font color="#000000">RC_CH3_PIN</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>
<font color="#00979c">void</font> <font color="#000000">calc_ch4</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">calc_input</font><font color="#000000">(</font><font color="#000000">RC_CH4</font><font color="#434f54">,</font> <font color="#000000">RC_CH4_PIN</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">setup</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">begin</font><font color="#000000">(</font><font color="#000000">SERIAL_PORT_SPEED</font><font color="#000000">)</font><font color="#000000">;</font>

 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">RC_CH1_PIN</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">RC_CH2_PIN</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">RC_CH3_PIN</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">RC_CH4_PIN</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">13</font><font color="#434f54">,</font> <font color="#00979c">OUTPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;
 &nbsp;<font color="#d35400">enableInterrupt</font><font color="#000000">(</font><font color="#000000">RC_CH1_PIN</font><font color="#434f54">,</font> <font color="#000000">calc_ch1</font><font color="#434f54">,</font> <font color="#00979c">CHANGE</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">enableInterrupt</font><font color="#000000">(</font><font color="#000000">RC_CH2_PIN</font><font color="#434f54">,</font> <font color="#000000">calc_ch2</font><font color="#434f54">,</font> <font color="#00979c">CHANGE</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">enableInterrupt</font><font color="#000000">(</font><font color="#000000">RC_CH3_PIN</font><font color="#434f54">,</font> <font color="#000000">calc_ch3</font><font color="#434f54">,</font> <font color="#00979c">CHANGE</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">enableInterrupt</font><font color="#000000">(</font><font color="#000000">RC_CH4_PIN</font><font color="#434f54">,</font> <font color="#000000">calc_ch4</font><font color="#434f54">,</font> <font color="#00979c">CHANGE</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">loop</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">rc_read_values</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;
 &nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;CH1:&#34;</font><font color="#000000">)</font><font color="#000000">;</font> <b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH1</font><font color="#000000">]</font><font color="#000000">)</font><font color="#000000">;</font> <b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;\t&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;CH2:&#34;</font><font color="#000000">)</font><font color="#000000">;</font> <b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH2</font><font color="#000000">]</font><font color="#000000">)</font><font color="#000000">;</font> <b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;\t&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;CH3:&#34;</font><font color="#000000">)</font><font color="#000000">;</font> <b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH3</font><font color="#000000">]</font><font color="#000000">)</font><font color="#000000">;</font> <b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;\t&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;CH4:&#34;</font><font color="#000000">)</font><font color="#000000">;</font> <b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">println</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH4</font><font color="#000000">]</font><font color="#000000">)</font><font color="#000000">;</font>

 &nbsp;<font color="#000000">ARLPM1</font> <font color="#434f54">=</font> <font color="#d35400">analogRead</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">ARLPM2</font> <font color="#434f54">=</font> <font color="#d35400">analogRead</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">ARRRM1</font> <font color="#434f54">=</font> <font color="#d35400">analogRead</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">ARRRM2</font> <font color="#434f54">=</font> <font color="#d35400">analogRead</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#000000">)</font><font color="#000000">;</font>

 &nbsp;<font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH1</font><font color="#000000">]</font> <font color="#434f54">&gt;</font><font color="#000000">1504</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH3</font><font color="#000000">]</font> <font color="#434f54">&lt;</font> <font color="#000000">1800</font><font color="#000000">)</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">130</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">165</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH1</font><font color="#000000">]</font> <font color="#434f54">&gt;</font> <font color="#000000">1800</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH3</font><font color="#000000">]</font> <font color="#434f54">&lt;</font> <font color="#000000">2040</font><font color="#000000">)</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">130</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">160</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH3</font><font color="#000000">]</font> <font color="#434f54">&gt;</font> <font color="#000000">1504</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH3</font><font color="#000000">]</font> <font color="#434f54">&lt;</font> <font color="#000000">1800</font><font color="#000000">)</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">130</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">165</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH3</font><font color="#000000">]</font> <font color="#434f54">&gt;</font> <font color="#000000">1800</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH3</font><font color="#000000">]</font> <font color="#434f54">&lt;</font> <font color="#000000">2040</font><font color="#000000">)</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">130</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">165</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH2</font><font color="#000000">]</font> <font color="#434f54">&lt;</font> <font color="#000000">1200</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font>
 &nbsp;<font color="#d35400">delay</font><font color="#000000">(</font><font color="#000000">200</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

</pre>
