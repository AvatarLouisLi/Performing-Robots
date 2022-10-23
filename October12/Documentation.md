# Two Videos and observation (Louis&Mudi)

[![Watch the video](https://img.youtube.com/vi/fSsN0cu_qvY/hqdefault.jpg)](https://youtu.be/fSsN0cu_qvY)

[![Watch the video](https://img.youtube.com/vi/lj89D_hT-GI/maxresdefault.jpg)](https://youtube.com/shorts/lj89D_hT-GI?feature=share)

# Observation:

I found the speech from the film "Rocky Balboa" and decided to use this to accompany our robot's performance (you can watch the clip online: https://youtu.be/5JAHAFvcr2o). This is not only because we think that it is a very inspirational speech and we like it a lot, but also because some of the scripts in it can be easily realized, such as "hit", "move forward". 

Before we shot the video, we were thinking about how to realize the "hit" scene, is it better for us to show up in the scene and hit the robot or control the robot to let it hit something? In the end, we decided to choose the latter. This is because we think it is important to showcase that we can control the robot remotely and smoothly. 

When we are controlling the robot, we utilize the big spin button to make the robot turn left and right, the small spin button to stop and start the robot, and the press button to make the robot move forward and backward. We think that this works well, but still there are still some spaces for us to improve. First, when we want to operate the robot to walk forward/backward and left/right at the same time, there will always be a pause between these two sets of actions. Though this doesn't bother us to shoot the video, we still do want to eliminate the pause and to realize the smooth transition between the two sets of movements.

# Our code: 

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

 &nbsp;<font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH2</font><font color="#000000">]</font> <font color="#434f54">&lt;</font> <font color="#000000">1000</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">155</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">165</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH2</font><font color="#000000">]</font> <font color="#434f54">&gt;</font> <font color="#000000">2000</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">155</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">165</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH1</font><font color="#000000">]</font> <font color="#434f54">&lt;</font> <font color="#000000">1000</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">120</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">155</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">165</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH1</font><font color="#000000">]</font> <font color="#434f54">&gt;</font> <font color="#000000">2000</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">150</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">120</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">165</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">rc_values</font><font color="#000000">[</font><font color="#000000">RC_CH3</font><font color="#000000">]</font> <font color="#434f54">&gt;</font> <font color="#000000">2000</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">LPM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM1</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">RRM2</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font>
 &nbsp;<font color="#d35400">delay</font><font color="#000000">(</font><font color="#000000">200</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

</pre>
